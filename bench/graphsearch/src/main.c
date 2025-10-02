#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <shmem.h>

#define DBG 1
#define MAX_LINE_LENGTH 1024
#define MAX_SEARCH_DEPTH 20000

// Dynamic array for size_t values
typedef struct {
    size_t* data;
    size_t length;
    size_t capacity;
} size_t_vec_t;

// Simple hash set for visited tracking
#define HASHSET_SIZE 65536
typedef struct {
    size_t* buckets;
    bool* occupied;
    size_t size;
} hashset_t;

// Edge structure for COO format
typedef struct {
    size_t row;
    size_t col;
    unsigned char value;
} edge_t;

// Simplified CRS Matrix structure
typedef struct {
    size_t rows;
    size_t cols;
    size_t* row_ptrs;      // Symmetric memory
    size_t* col_indices;   // Symmetric memory
    unsigned char* values; // Symmetric memory
    size_t total_nnz;
} crs_matrix_t;

// Timing utility
double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

// Parse edge from line "row,col"
bool parse_edge(const char* line, size_t* row, size_t* col) {
    char* endptr;
    char* comma = strchr(line, ',');
    if (!comma) return false;
    
    *row = strtoul(line, &endptr, 10);
    if (endptr != comma) return false;
    
    *col = strtoul(comma + 1, &endptr, 10);
    return *endptr == '\0' || *endptr == '\n';
}

// Dynamic array functions
bool vec_init(size_t_vec_t* vec, size_t initial_capacity) {
    vec->capacity = initial_capacity > 0 ? initial_capacity : 16;
    vec->data = malloc(vec->capacity * sizeof(size_t));
    vec->length = 0;
    return vec->data != NULL;
}

void vec_free(size_t_vec_t* vec) {
    if (vec->data) {
        free(vec->data);
        vec->data = NULL;
    }
    vec->length = 0;
    vec->capacity = 0;
}

bool vec_push(size_t_vec_t* vec, size_t value) {
    if (vec->length >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;
        size_t* new_data = realloc(vec->data, new_capacity * sizeof(size_t));
        if (!new_data) return false;
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->length++] = value;
    return true;
}

void vec_clear(size_t_vec_t* vec) {
    vec->length = 0;
}

// Comparison function for qsort
int size_t_compare(const void* a, const void* b) {
    size_t sa = *(const size_t*)a;
    size_t sb = *(const size_t*)b;
    if (sa < sb) return -1;
    if (sa > sb) return 1;
    return 0;
}

// Sort and remove duplicates
void vec_sort_unique(size_t_vec_t* vec) {
    if (vec->length <= 1) return;
    
    qsort(vec->data, vec->length, sizeof(size_t), size_t_compare);
    
    size_t write_idx = 1;
    for (size_t read_idx = 1; read_idx < vec->length; read_idx++) {
        if (vec->data[read_idx] != vec->data[write_idx - 1]) {
            vec->data[write_idx++] = vec->data[read_idx];
        }
    }
    vec->length = write_idx;
}

// Hash set functions
bool hashset_init(hashset_t* set) {
    set->buckets = calloc(HASHSET_SIZE, sizeof(size_t));
    set->occupied = calloc(HASHSET_SIZE, sizeof(bool));
    set->size = 0;
    return set->buckets != NULL && set->occupied != NULL;
}

void hashset_free(hashset_t* set) {
    if (set->buckets) free(set->buckets);
    if (set->occupied) free(set->occupied);
    set->buckets = NULL;
    set->occupied = NULL;
    set->size = 0;
}

size_t hash_func(size_t key) {
    return key % HASHSET_SIZE;
}

bool hashset_contains(hashset_t* set, size_t key) {
    size_t idx = hash_func(key);
    size_t orig_idx = idx;
    
    while (set->occupied[idx]) {
        if (set->buckets[idx] == key) return true;
        idx = (idx + 1) % HASHSET_SIZE;
        if (idx == orig_idx) break;
    }
    return false;
}

bool hashset_insert(hashset_t* set, size_t key) {
    if (hashset_contains(set, key)) return true;
    
    size_t idx = hash_func(key);
    while (set->occupied[idx]) {
        idx = (idx + 1) % HASHSET_SIZE;
    }
    
    set->buckets[idx] = key;
    set->occupied[idx] = true;
    set->size++;
    return true;
}

// Binary search for sorted array
bool binary_search(const size_t* arr, size_t len, size_t target) {
    size_t left = 0;
    size_t right = len;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) return true;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return false;
}

// Get column indices for a row in CRS matrix
size_t* get_cols_on_row(const crs_matrix_t* matrix, size_t row, size_t* count) {
    if (row >= matrix->rows) {
        *count = 0;
        return NULL;
    }
    
    size_t start = matrix->row_ptrs[row];
    size_t end = matrix->row_ptrs[row + 1];
    *count = end - start;
    
    if (*count == 0) return NULL;
    return &matrix->col_indices[start];
}

// Edge comparison function for sorting
int edge_compare(const void* a, const void* b) {
    const edge_t* ea = (const edge_t*)a;
    const edge_t* eb = (const edge_t*)b;
    
    if (ea->row < eb->row) return -1;
    if (ea->row > eb->row) return 1;
    if (ea->col < eb->col) return -1;
    if (ea->col > eb->col) return 1;
    return 0;
}

// Create CRS matrix from distributed edges
crs_matrix_t* create_matrix_from_edges(edge_t* local_edges, size_t local_edge_count, size_t max_vertex) {
    int mpe = shmem_my_pe();
    int npes = shmem_n_pes();
    
    size_t matrix_size = max_vertex + 1;
    
    // Collect edge counts from all PEs
    size_t* all_edge_counts = shmem_malloc(npes * sizeof(size_t));
    if (!all_edge_counts) return NULL;
    
    shmem_barrier_all();
    for (int pe = 0; pe < npes; pe++) {
        shmem_size_p(&all_edge_counts[pe], local_edge_count, pe);
    }
    shmem_barrier_all();
    
    size_t total_edges = 0;
    for (int i = 0; i < npes; i++) {
        total_edges += all_edge_counts[i];
    }
    
    // Allocate matrix
    crs_matrix_t* matrix = malloc(sizeof(crs_matrix_t));
    if (!matrix) {
        shmem_free(all_edge_counts);
        return NULL;
    }
    
    matrix->rows = matrix_size;
    matrix->cols = matrix_size;
    matrix->total_nnz = total_edges;
    
    // Allocate symmetric memory
    matrix->row_ptrs = shmem_calloc(matrix_size + 1, sizeof(size_t));
    matrix->col_indices = shmem_malloc(total_edges * sizeof(size_t));
    matrix->values = shmem_malloc(total_edges * sizeof(unsigned char));
    
    if (!matrix->row_ptrs || !matrix->col_indices || !matrix->values) {
        if (matrix->row_ptrs) shmem_free(matrix->row_ptrs);
        if (matrix->col_indices) shmem_free(matrix->col_indices);
        if (matrix->values) shmem_free(matrix->values);
        free(matrix);
        shmem_free(all_edge_counts);
        return NULL;
    }
    
    // PE 0 collects all edges, sorts them, and builds CRS structure
    if (mpe == 0) {
        edge_t* all_edges = malloc(total_edges * sizeof(edge_t));
        if (!all_edges) {
            shmem_free(matrix->row_ptrs);
            shmem_free(matrix->col_indices);
            shmem_free(matrix->values);
            free(matrix);
            shmem_free(all_edge_counts);
            return NULL;
        }
        
        size_t offset = 0;
        for (int pe = 0; pe < npes; pe++) {
            size_t pe_edge_count = all_edge_counts[pe];
            if (pe == 0) {
                memcpy(&all_edges[offset], local_edges, pe_edge_count * sizeof(edge_t));
            } else {
                shmem_getmem(&all_edges[offset], local_edges, pe_edge_count * sizeof(edge_t), pe);
            }
            offset += pe_edge_count;
        }
        
        // Sort edges by row, then column
        qsort(all_edges, total_edges, sizeof(edge_t), edge_compare);
        
        // Build CRS structure
        size_t current_row = 0;
        matrix->row_ptrs[0] = 0;
        
        for (size_t i = 0; i < total_edges; i++) {
            // Fill in empty rows
            while (current_row < all_edges[i].row) {
                current_row++;
                matrix->row_ptrs[current_row] = i;
            }
            
            matrix->col_indices[i] = all_edges[i].col;
            matrix->values[i] = all_edges[i].value;
        }
        
        // Fill remaining row pointers
        while (current_row < matrix_size) {
            current_row++;
            matrix->row_ptrs[current_row] = total_edges;
        }
        
        free(all_edges);
    }
    
    shmem_barrier_all();
    shmem_free(all_edge_counts);
    
    return matrix;
}

void free_matrix(crs_matrix_t* matrix) {
    if (matrix) {
        if (matrix->row_ptrs) shmem_free(matrix->row_ptrs);
        if (matrix->col_indices) shmem_free(matrix->col_indices);
        if (matrix->values) shmem_free(matrix->values);
        free(matrix);
    }
}

// BFS implementation
size_t bfs(const crs_matrix_t* matrix, size_t from, size_t to) {
    if (from == to) return 0;
    
    size_t_vec_t q_targets, q_scratch;
    hashset_t seen;
    
    if (!vec_init(&q_targets, 256) || 
        !vec_init(&q_scratch, 256) ||
        !hashset_init(&seen)) {
        vec_free(&q_targets);
        vec_free(&q_scratch);
        hashset_free(&seen);
        return SIZE_MAX;
    }
    
    // Initialize first level
    size_t count;
    size_t* neighbors = get_cols_on_row(matrix, from, &count);
    for (size_t i = 0; i < count; i++) {
        vec_push(&q_targets, neighbors[i]);
    }
    vec_sort_unique(&q_targets);
    
    size_t layers = 1;
    
    while (q_targets.length > 0 && layers <= MAX_SEARCH_DEPTH) {
        // Check if target is in current queue
        if (binary_search(q_targets.data, q_targets.length, to)) {
            vec_free(&q_targets);
            vec_free(&q_scratch);
            hashset_free(&seen);
            return layers;
        }
        
        // Build next level
        vec_clear(&q_scratch);
        for (size_t i = 0; i < q_targets.length; i++) {
            size_t node = q_targets.data[i];
            size_t* node_neighbors = get_cols_on_row(matrix, node, &count);
            for (size_t j = 0; j < count; j++) {
                if (!hashset_contains(&seen, node_neighbors[j])) {
                    vec_push(&q_scratch, node_neighbors[j]);
                }
            }
        }
        
        // Mark current level as seen
        for (size_t i = 0; i < q_targets.length; i++) {
            hashset_insert(&seen, q_targets.data[i]);
        }
        
        vec_sort_unique(&q_scratch);
        
        // Check for infinite loop
        if (layers > 20000 || (q_scratch.length == q_targets.length && 
            memcmp(q_scratch.data, q_targets.data, q_targets.length * sizeof(size_t)) == 0)) {
#ifdef DBG
            fprintf(stderr, "PE %d: BFS infinite loop detected at layer %zu\n", shmem_my_pe(), layers);
#endif
            break;
        }
        
        // Swap queues
        size_t_vec_t temp = q_targets;
        q_targets = q_scratch;
        q_scratch = temp;
        
        layers++;
    }
    
    vec_free(&q_targets);
    vec_free(&q_scratch);
    hashset_free(&seen);
    
    return SIZE_MAX; // Not found
}

int main(int argc, char* argv[]) {
    shmem_init();
    
    // Check command line arguments
    if (argc != 3) {
        if (shmem_my_pe() == 0) {
            fprintf(stderr, "Usage: %s <searchlist> <edgelist>\n", argv[0]);
        }
        shmem_global_exit(1);
    }
    
    const char* searchlist_file = argv[1];
    const char* edgelist_file = argv[2];
    
    double start_time = get_time();
    int mpe = shmem_my_pe();
    int npes = shmem_n_pes();

#ifdef DBG
    fprintf(stderr, "Hello, world!\n");
    fprintf(stderr, "[PE %2d] start reading edgelist: %s\n", mpe, edgelist_file);
#endif
    
    // Read edgelist file
    FILE* file = fopen(edgelist_file, "r");
    if (!file) {
        fprintf(stderr, "PE %d: Cannot open edgelist file: %s\n", mpe, edgelist_file);
        shmem_global_exit(1);
    }
    
    // Count total lines
    size_t total_lines = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        total_lines++;
    }
    rewind(file);

#ifdef DBG
    fprintf(stderr, "[PE %2d] read edgelist\n", mpe);
    fprintf(stderr, "[PE %2d] start parse edgelist\n", mpe);
#endif
    
    // Calculate lines per PE
    size_t lines_per_pe = (total_lines + npes - 1) / npes;
    size_t start_line = mpe * lines_per_pe;
    size_t end_line = (mpe + 1) * lines_per_pe;
    if (end_line > total_lines) end_line = total_lines;
    
    // Parse edges for this PE
    edge_t* edges = malloc(lines_per_pe * sizeof(edge_t));
    size_t edge_count = 0;
    size_t local_max = 0;
    
    size_t current_line = 0;
    while (fgets(line, sizeof(line), file) && current_line < end_line) {
        if (current_line >= start_line) {
            size_t row, col;
            if (parse_edge(line, &row, &col)) {
                edges[edge_count].row = row;
                edges[edge_count].col = col;
                edges[edge_count].value = 1;
                edge_count++;
                
                size_t max_val = (row > col) ? row : col;
                if (max_val > local_max) local_max = max_val;
            }
        }
        current_line++;
    }
    fclose(file);

#ifdef DBG
    fprintf(stderr, "[PE %2d] parsed %zu edges from edgelist\n", mpe, edge_count);
#endif
    
    // Find global maximum vertex
    size_t* global_max_ptr = shmem_malloc(sizeof(size_t));
    
    shmem_barrier_all();
    shmem_size_max_reduce(SHMEM_TEAM_WORLD, global_max_ptr, &local_max, 1);
    size_t global_max = *global_max_ptr;
    
    if (mpe == 0) {
        fprintf(stderr, "[PE %2d] adj matrix dimensions: %zux%zu\n", mpe, global_max + 1, global_max + 1);
    }
    
    fprintf(stderr, "[PE %2d] storing %zu edges into adj matrix\n", mpe, edge_count);
    
    // Create matrix from edges
    crs_matrix_t* matrix = create_matrix_from_edges(edges, edge_count, global_max);
    free(edges);
    
    if (!matrix) {
        fprintf(stderr, "PE %d: Failed to create matrix\n", mpe);
        shmem_global_exit(1);
    }
    
    fprintf(stderr, "[PE %2d] global edges: %zu\n", mpe, matrix->total_nnz);
    
    fprintf(stderr, "[PE %2d] parsing searchlist: %s...\n", mpe, searchlist_file);
    
    // Read searchlist file
    file = fopen(searchlist_file, "r");
    if (!file) {
        fprintf(stderr, "PE %d: Cannot open searchlist file: %s\n", mpe, searchlist_file);
        shmem_global_exit(1);
    }
    
    // Count search lines
    size_t total_search_lines = 0;
    while (fgets(line, sizeof(line), file)) {
        total_search_lines++;
    }
    rewind(file);
    
    // Parse search pairs for this PE
    size_t search_lines_per_pe = (total_search_lines + npes - 1) / npes;
    size_t search_start_line = mpe * search_lines_per_pe;
    size_t search_end_line = (mpe + 1) * search_lines_per_pe;
    if (search_end_line > total_search_lines) search_end_line = total_search_lines;
    
    typedef struct { size_t from, to; } search_pair_t;
    search_pair_t* searches = malloc(search_lines_per_pe * sizeof(search_pair_t));
    size_t search_count = 0;
    
    current_line = 0;
    while (fgets(line, sizeof(line), file) && current_line < search_end_line) {
        if (current_line >= search_start_line) {
            if (parse_edge(line, &searches[search_count].from, &searches[search_count].to)) {
                search_count++;
            }
        }
        current_line++;
    }
    fclose(file);
    
    fprintf(stderr, "[PE %2d] parsed %zu searchpairs\n", mpe, total_search_lines);
    
    // Perform BFS searches
    size_t* distances = malloc(search_count * sizeof(size_t));
    fprintf(stderr, "[PE %2d] starting searches!\n", mpe);
    
    for (size_t i = 0; i < search_count; i++) {
        fprintf(stderr, "[PE %2d]search #%4zu: %10zu -> %10zu...\n", mpe, i, searches[i].from, searches[i].to);
        distances[i] = bfs(matrix, searches[i].from, searches[i].to);
    }
    
    // Statistics (simplified - only PE 0's local results)
    if (mpe == 0 && search_count > 0) {
        size_t min_dist = SIZE_MAX;
        size_t max_dist = 0;
        double total_dist = 0;
        size_t valid_searches = 0;
        
        for (size_t i = 0; i < search_count; i++) {
            if (distances[i] != SIZE_MAX) {
                if (distances[i] < min_dist) min_dist = distances[i];
                if (distances[i] > max_dist) max_dist = distances[i];
                total_dist += distances[i];
                valid_searches++;
            }
        }
        
        double elapsed = get_time() - start_time;
        fprintf(stderr, "%zu searches in %.3fs\n", total_search_lines, elapsed);
        printf("%.3f\n", total_search_lines / elapsed);
    }
    
    // Cleanup
    free(searches);
    free(distances);
    free_matrix(matrix);
    shmem_free(global_max_ptr);
    
    shmem_finalize();
    return 0;
}
