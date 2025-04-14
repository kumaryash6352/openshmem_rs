#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <shmem.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <math.h>

#define BYTES_PER_MIB (1024.0 * 1024.0)
#define US_PER_S      1000000.0
#define NS_PER_S      1000000000.0
#define MAX_MSG_SIZES 128


typedef enum {
    ROUTINE_GET,
    ROUTINE_PUT,
    ROUTINE_ATOMICADD,
    ROUTINE_ATOMICCMPSWP,
    ROUTINE_ATOMICFETCH,
    ROUTINE_ATOMICINC,
    ROUTINE_BARRIER,
    ROUTINE_UNKNOWN
} RoutineType;

RoutineType routine_from_string(const char *s);
const char* routine_to_string(RoutineType r);
int uses_msg_size(RoutineType r);
int parse_msg_sizes(const char *value, size_t sizes[], int *count);
int generate_powers_of_2(size_t max_val, size_t sizes[], int *count);
void print_info_header(const char *shmemname, int major, int minor, int n_pes,
                       RoutineType benchname, long ntimes,
                       size_t msg_sizes[], int num_sizes);
void print_results_header();
long long timespec_diff_ns(struct timespec start, struct timespec end);
size_t find_max_size(size_t arr[], int n);
size_t find_min_size(size_t arr[], int n);

void bench_get(long ntimes, size_t sizes[], int num_sizes);
void bench_put(long ntimes, size_t sizes[], int num_sizes);
void bench_atomic_add(long ntimes);
void bench_atomic_cmp_swp(long ntimes);
void bench_atomic_fetch(long ntimes);
void bench_atomic_inc(long ntimes);
void bench_barrier(long ntimes);

int my_pe = -1;
int n_pes = -1;

int main(int argc, char *argv[]) {
    RoutineType bench_type = ROUTINE_UNKNOWN;
    long ntimes = 1000;
    size_t msg_size_max = 0;
    char *msg_sizes_str = NULL;
    size_t msg_sizes[MAX_MSG_SIZES];
    int num_msg_sizes = 0;
    int opt;
    int is_root = 0;

    struct option long_options[] = {
        {"bench", required_argument, 0, 'b'},
        {"ntimes", required_argument, 0, 'n'},
        {"msg-size-max", required_argument, 0, 's'},
        {"msg-sizes", required_argument, 0, 'M'},
        {0, 0, 0, 0}
    };

    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "b:n:s:M:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'b':
                bench_type = routine_from_string(optarg);
                if (bench_type == ROUTINE_UNKNOWN) {
                    fprintf(stderr, "Error: Invalid benchmark routine '%s'. Choices: get, put, atomic-add, atomic-cmp-swp, atomic-fetch, atomic-inc, barrier\n", optarg);
                    return EXIT_FAILURE;
                }
                break;
            case 'n':
                ntimes = atol(optarg);
                if (ntimes <= 0) {
                    fprintf(stderr, "Error: ntimes must be a positive integer.\n");
                    return EXIT_FAILURE;
                }
                break;
            case 's':
                msg_size_max = (size_t)atoll(optarg);
                 if (msg_size_max == 0 && strcmp(optarg, "0") != 0) {
                    fprintf(stderr, "Error: Invalid value for --msg-size-max: %s\n", optarg);
                    return EXIT_FAILURE;
                 }
                break;
            case 'M':
                msg_sizes_str = optarg;
                break;
            case '?':
                return EXIT_FAILURE;
            default:
                // don't really know how to get here
                abort();
        }
    }

    if (bench_type == ROUTINE_UNKNOWN) {
        fprintf(stderr, "Error: Benchmark routine (-b or --bench) is required.\n");
        return EXIT_FAILURE;
    }

    if (msg_size_max > 0 && msg_sizes_str != NULL) {
        fprintf(stderr, "Error: --msg-size-max (-s) and --msg-sizes (-M) are mutually exclusive.\n");
        return EXIT_FAILURE;
    }

    shmem_init();
    my_pe = shmem_my_pe();
    n_pes = shmem_n_pes();
    is_root = (my_pe == 0);

    if (uses_msg_size(bench_type)) {
        if (msg_sizes_str) {
            if (!parse_msg_sizes(msg_sizes_str, msg_sizes, &num_msg_sizes)) {
                if (is_root) fprintf(stderr, "Error parsing --msg-sizes: '%s'. Must be comma-separated positive integers.\n", msg_sizes_str);
                shmem_finalize();
                return EXIT_FAILURE;
            }
        } else if (msg_size_max > 0) {
            if (msg_size_max < 1) {
                if (is_root) fprintf(stderr, "Error: --msg-size-max must be at least 1.\n");
                shmem_finalize();
                return EXIT_FAILURE;
            }
            if (!generate_powers_of_2(msg_size_max, msg_sizes, &num_msg_sizes)) {
                if (is_root) fprintf(stderr, "Error generating powers of 2 (maybe MAX_MSG_SIZES too small?).\n");
                shmem_finalize();
                return EXIT_FAILURE;
            }
        } else {
            // 2 up to 1 MiB
            if (!generate_powers_of_2(1 << 20, msg_sizes, &num_msg_sizes)) {
                 if (is_root) fprintf(stderr, "Error generating default powers of 2.\n");
                 shmem_finalize();
                 return EXIT_FAILURE;
            }
        }

        if (num_msg_sizes == 0) {
            if (is_root) fprintf(stderr, "Error: No valid message sizes specified or generated for a benchmark that requires them.\n");
            shmem_finalize();
            return EXIT_FAILURE;
        }
    }

    if (is_root) {
        char name[SHMEM_MAX_NAME_LEN];
        int major, minor;
        shmem_info_get_name(name);
        shmem_info_get_version(&major, &minor);
        print_info_header(name, major, minor, n_pes, bench_type, ntimes, msg_sizes, num_msg_sizes);
    }

    switch (bench_type) {
        case ROUTINE_GET:
            bench_get(ntimes, msg_sizes, num_msg_sizes);
            break;
        case ROUTINE_PUT:
            bench_put(ntimes, msg_sizes, num_msg_sizes);
            break;
        case ROUTINE_ATOMICADD:
            bench_atomic_add(ntimes);
            break;
        case ROUTINE_ATOMICCMPSWP:
            bench_atomic_cmp_swp(ntimes);
            break;
        case ROUTINE_ATOMICFETCH:
            bench_atomic_fetch(ntimes);
            break;
        case ROUTINE_ATOMICINC:
            bench_atomic_inc(ntimes);
            break;
        case ROUTINE_BARRIER:
            bench_barrier(ntimes);
            break;
        default:
             if (is_root) fprintf(stderr, "Error: Unknown benchmark routine selected internally.\n");
             shmem_finalize();
             return EXIT_FAILURE;
    }

    shmem_finalize();
    return EXIT_SUCCESS;
}

RoutineType routine_from_string(const char *s) {
    if (strcmp(s, "get") == 0) return ROUTINE_GET;
    if (strcmp(s, "put") == 0) return ROUTINE_PUT;
    if (strcmp(s, "atomic-add") == 0) return ROUTINE_ATOMICADD;
    if (strcmp(s, "atomic-cmp-swp") == 0) return ROUTINE_ATOMICCMPSWP;
    if (strcmp(s, "atomic-fetch") == 0) return ROUTINE_ATOMICFETCH;
    if (strcmp(s, "atomic-inc") == 0) return ROUTINE_ATOMICINC;
    if (strcmp(s, "barrier") == 0) return ROUTINE_BARRIER;
    return ROUTINE_UNKNOWN;
}

const char* routine_to_string(RoutineType r) {
    switch(r) {
        case ROUTINE_GET: return "GET";
        case ROUTINE_PUT: return "PUT";
        case ROUTINE_ATOMICADD: return "ATOMICADD";
        case ROUTINE_ATOMICCMPSWP: return "ATOMICCMPSWP";
        case ROUTINE_ATOMICFETCH: return "ATOMICFETCH";
        case ROUTINE_ATOMICINC: return "ATOMICINC";
        case ROUTINE_BARRIER: return "BARRIER";
        default: return "UNKNOWN";
    }
}

int uses_msg_size(RoutineType r) {
    return r == ROUTINE_GET || r == ROUTINE_PUT;
}

int parse_msg_sizes(const char *value, size_t sizes[], int *count) {
    char *str = strdup(value);
    if (!str) {
        perror("strdup failed");
        *count = 0;
        return 0;
    }
    char *token;
    char *endptr;
    *count = 0;
    int success = 1;

    token = strtok(str, ",");
    while (token != NULL) {
        if (*count >= MAX_MSG_SIZES) {
            fprintf(stderr, "Warning: Exceeded maximum number of message sizes (%d). Ignoring remaining.\n", MAX_MSG_SIZES);
            success = 0;
            break;
        }
        errno = 0;
        long long val = strtoll(token, &endptr, 10);


        if (errno != 0 || *endptr != '\0' || val <= 0 || val > SIZE_MAX) {
            success = 0;
            break;
        }
        sizes[*count] = (size_t)val;
        (*count)++;
        token = strtok(NULL, ",");
    }

    free(str);
    if (*count == 0 && success) {
        success = 0;
    }
    return success;
}


int generate_powers_of_2(size_t max_val, size_t sizes[], int *count) {
    *count = 0;
    if (max_val < 1) {
        return 1;
    }
    size_t x = 1;
    while (x <= max_val) {
         if (*count >= MAX_MSG_SIZES) {
            fprintf(stderr, "Warning: Exceeded maximum number of message sizes (%d) while generating powers of 2.\n", MAX_MSG_SIZES);
            return 0;
        }
        sizes[*count] = x;
        (*count)++;
        if (max_val / 2 < x) break;
        x *= 2;
    }
    return 1;
}

void print_info_header(const char *shmemname, int major, int minor, int n_pes_val,
                       RoutineType benchname, long ntimes_val,
                       size_t msg_sizes[], int num_sizes) {
    printf("==============================================\n");
    printf("===         Test Information               ===\n");
    printf("==============================================\n");
    printf("  OpenSHMEM Name:         %s\n", shmemname);
    printf("  OpenSHMEM Version:      %d.%d\n", major, minor);
    printf("  Bindings Version:       N/A (C)\n");
    printf("  Number of PEs:          %d\n", n_pes_val);
    printf("  Benchmark:              %s\n", routine_to_string(benchname));
    if (uses_msg_size(benchname) && num_sizes > 0) {
        printf("  Min Msg Size (bytes):   %zu\n", find_min_size(msg_sizes, num_sizes));
        printf("  Max Msg Size (bytes):   %zu\n", find_max_size(msg_sizes, num_sizes));
    }
    printf("  Ntimes:                 %ld\n", ntimes_val);
}

void print_results_header() {
    printf("==============================================\n");
    printf("===         Benchmark Results              ===\n");
    printf("==============================================\n");
}

long long timespec_diff_ns(struct timespec start, struct timespec end) {
    return (long long)(end.tv_sec - start.tv_sec) * NS_PER_S + (end.tv_nsec - start.tv_nsec);
}

size_t find_max_size(size_t arr[], int n) {
    if (n <= 0) return 0;
    size_t max_val = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

size_t find_min_size(size_t arr[], int n) {
    if (n <= 0) return 0;
    size_t min_val = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}


void bench_atomic_inc(long ntimes) {
    int *dest = (int *)shmem_calloc(1, sizeof(int));
    if (!dest) {
        perror("shmem_calloc failed for dest");
        return;
    }

    int target_pe = 0;

    shmem_barrier_all();
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (long i = 0; i < ntimes; ++i) {
        shmem_atomic_inc(dest, target_pe);
    }

    shmem_quiet();
    shmem_barrier_all();
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    if (my_pe == 0) {
        long long elapsed_ns = timespec_diff_ns(start_time, end_time);
        double elapsed_us = (double)elapsed_ns / 1000.0;
        double avg_us = elapsed_us / ntimes;
        print_results_header();
        printf("Avg Time per Increment (us): %.8f (%.2f total us)\n", avg_us, elapsed_us);
    }

    shmem_barrier_all();
    shmem_free(dest);
}

void bench_atomic_cmp_swp(long ntimes) {
    int *dest = (int *)shmem_calloc(1, sizeof(int));
     if (!dest) {
        perror("shmem_calloc failed for dest");
        return;
    }
    int target_pe = 0;
    int my_rank_int = my_pe;
    int swp_with = my_rank_int;
    int if_eqs = 0;

    shmem_barrier_all();
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (long i = 0; i < ntimes; ++i) {
        shmem_atomic_compare_swap(dest, if_eqs, swp_with, target_pe);
    }

    shmem_quiet();
    shmem_barrier_all();
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    if (my_pe == 0) {
        long long elapsed_ns = timespec_diff_ns(start_time, end_time);
        double elapsed_us = (double)elapsed_ns / 1000.0;
        double avg_us = elapsed_us / ntimes;
        print_results_header();
        printf("Avg Time per Compare+Swap (us): %.8f (%.2f total us)\n", avg_us, elapsed_us);
    }

    shmem_barrier_all();
    shmem_free(dest);
}

void bench_atomic_fetch(long ntimes) {
    int *dest = (int *)shmem_calloc(1, sizeof(int));
     if (!dest) {
        perror("shmem_calloc failed for dest");
        return;
    }
    int target_pe = 0;

    shmem_barrier_all();
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    volatile int fetched_val;
    for (long i = 0; i < ntimes; ++i) {
        fetched_val = shmem_atomic_fetch(dest, target_pe);
    }
    (void)fetched_val;

    shmem_quiet();
    shmem_barrier_all();
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    if (my_pe == 0) {
        long long elapsed_ns = timespec_diff_ns(start_time, end_time);
        double elapsed_us = (double)elapsed_ns / 1000.0;
        double avg_us = elapsed_us / ntimes;
        print_results_header();
        printf("Avg Time per Fetch (us): %.8f (%.2f total us)\n", avg_us, elapsed_us);
    }

    shmem_barrier_all();
    shmem_free(dest);
}


void bench_atomic_add(long ntimes) {
    int *dest = (int *)shmem_calloc(1, sizeof(int));
     if (!dest) {
        perror("shmem_calloc failed for dest");
        return;
    }
    int target_pe = 0;
    int value_to_add = 1;

    shmem_barrier_all();
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (long i = 0; i < ntimes; ++i) {
        shmem_atomic_add(dest, value_to_add, target_pe);
    }

    shmem_quiet();
    shmem_barrier_all();
    clock_gettime(CLOCK_MONOTONIC, &end_time);

     if (my_pe == 0) {
        long long elapsed_ns = timespec_diff_ns(start_time, end_time);
        double elapsed_us = (double)elapsed_ns / 1000.0;
        double avg_us = elapsed_us / ntimes;
        print_results_header();
        printf("Avg Time per Add (us): %.8f (%.2f total us)\n", avg_us, elapsed_us);
    }

    shmem_barrier_all();
    shmem_free(dest);
}

void bench_put(long ntimes, size_t sizes[], int num_sizes) {
    if (num_sizes == 0) return;
    size_t max_msg = find_max_size(sizes, num_sizes);


    char *dest = (char *)shmem_malloc(max_msg);
    char *src = (char *)shmem_malloc(max_msg);

    if (!dest || !src) {
        perror("shmem_malloc failed for put buffers");
        if (dest) shmem_free(dest);
        if (src) shmem_free(src);
        return;
    }

    int target_pe = 0;


    for (size_t i = 0; i < max_msg; ++i) {
        src[i] = (char)(i % 256);
    }

    double *total_times = (double*)malloc(num_sizes * sizeof(double));
    if (!total_times) {
        perror("malloc failed for timing array");
        shmem_free(dest);
        shmem_free(src);
        return;
    }


    shmem_barrier_all();

    struct timespec start_time, end_time;
    for (int s_idx = 0; s_idx < num_sizes; ++s_idx) {
        size_t current_size = sizes[s_idx];

        shmem_barrier_all();
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        for (long i = 0; i < ntimes; ++i) {
             shmem_putmem(dest, src, current_size, target_pe);
        }

        shmem_quiet();
        shmem_barrier_all();
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        long long elapsed_ns = timespec_diff_ns(start_time, end_time);
        total_times[s_idx] = (double)elapsed_ns / NS_PER_S;
    }

    if (my_pe == 0) {
        print_results_header();
        printf("%-10s\t%15s\t%18s\n", "size (B)", "latency (us)", "bandwidth (MiB/s)");
        printf("------------------------------------------------------------\n");
        for (int s_idx = 0; s_idx < num_sizes; ++s_idx) {
            size_t size = sizes[s_idx];
            double total_time_s = total_times[s_idx];
            if (total_time_s > 0) {
                double latency_s = total_time_s / ntimes;
                double latency_us = latency_s * US_PER_S;
                double bandwidth_mib_s = (size * ntimes) / total_time_s / BYTES_PER_MIB;
                printf("%-10zu\t%15.2f\t%18.2f\n", size, latency_us, bandwidth_mib_s);
            } else {
                printf("%-10zu\t%15s\t%18s\n", size, "inf", "inf");
            }
        }
    }

    shmem_barrier_all();
    shmem_free(dest);
    shmem_free(src);
    free(total_times);
}

void bench_get(long ntimes, size_t sizes[], int num_sizes) {
    if (num_sizes == 0) return;
    size_t max_msg = find_max_size(sizes, num_sizes);

    char *src = (char *)shmem_malloc(max_msg);
    char *dest_local = (char *)malloc(max_msg);

    if (!src) {
        perror("shmem_malloc failed for remote source buffer");
        if(dest_local) free(dest_local);
        return;
    }
     if (!dest_local) {
        perror("malloc failed for local destination buffer");
        shmem_free(src);
        return;
    }

    int source_pe = 0;

    for (size_t i = 0; i < max_msg; ++i) {
        src[i] = (char)(i % 256);
    }

    double *total_times = (double*)malloc(num_sizes * sizeof(double));
    if (!total_times) {
        perror("malloc failed for timing array");
        shmem_free(src);
        free(dest_local);
        return;
    }

    shmem_barrier_all();

    struct timespec start_time, end_time;
    for (int s_idx = 0; s_idx < num_sizes; ++s_idx) {
        size_t current_size = sizes[s_idx];

        shmem_barrier_all();
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        for (long i = 0; i < ntimes; ++i) {

             shmem_getmem(dest_local, src, current_size, source_pe);
        }

        shmem_quiet();
        shmem_barrier_all();
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        long long elapsed_ns = timespec_diff_ns(start_time, end_time);
        total_times[s_idx] = (double)elapsed_ns / NS_PER_S;
    }

     if (my_pe == 0) {
        print_results_header();
        printf("%-10s\t%15s\t%18s\n", "size (B)", "latency (us)", "bandwidth (MiB/s)");
        printf("------------------------------------------------------------\n");
        for (int s_idx = 0; s_idx < num_sizes; ++s_idx) {
            size_t size = sizes[s_idx];
            double total_time_s = total_times[s_idx];
            if (total_time_s > 0) {
                double latency_s = total_time_s / ntimes;
                double latency_us = latency_s * US_PER_S;
                double bandwidth_mib_s = (size * ntimes) / total_time_s / BYTES_PER_MIB;
                printf("%-10zu\t%15.2f\t%18.2f\n", size, latency_us, bandwidth_mib_s);
            } else {
                printf("%-10zu\t%15s\t%18s\n", size, "inf", "inf");
            }
        }
    }

    shmem_barrier_all();
    shmem_free(src);
    free(dest_local);
    free(total_times);
}

void bench_barrier(long ntimes) {
    shmem_barrier_all();

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (long i = 0; i < ntimes; ++i) {
        shmem_barrier_all();
    }


    clock_gettime(CLOCK_MONOTONIC, &end_time);

     if (my_pe == 0) {
        long long elapsed_ns = timespec_diff_ns(start_time, end_time);
        double elapsed_us = (double)elapsed_ns / 1000.0;
        double avg_us = elapsed_us / ntimes;
        print_results_header();
        printf("Avg Time per Barrier (us): %.8f (%.2f total us)\n", avg_us, elapsed_us);
    }

    shmem_barrier_all();
}
