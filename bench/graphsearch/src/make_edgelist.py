#!/usr/bin/env python3

from math import ceil
import numpy as np
import argparse

def main():
    parser = argparse.ArgumentParser(description='Generate edge list and search pairs for graph search benchmarking')
    parser.add_argument('--nodes', type=int, default=128, help='Number of nodes in the graph (default: 128)')
    parser.add_argument('--n-searches', type=int, default=16, help='Number of search pairs to generate (default: 16)')
    parser.add_argument('--max-path-len', type=int, default=16, help='Maximum path length for search pairs (default: 16)')
    parser.add_argument('--seed', type=int, default=42, help='Random seed for reproducibility (default: 42)')
    parser.add_argument('--edgelist-output', type=str, default='edgelist', help='Output file for edge list (default: edgelist)')
    parser.add_argument('--searchlist-output', type=str, default='searchlist', help='Output file for search pairs (default: searchlist)')
    
    args = parser.parse_args()
    
    nodes = args.nodes
    n_searches = args.n_searches
    max_path_len = args.max_path_len
    
    np.random.seed(args.seed)
    
    n_edges = ceil(pow(nodes, 2) / 16) - n_searches * max_path_len

    print(f"generating {n_edges} edges...")
    edges = np.random.randint(0, nodes, size=(n_edges, 2))
    
    print(f"generating {n_searches} search pairs...")
    searches = np.random.randint(0, nodes, size=(n_searches, 2))
    
    print(f"ensuring search pairs can be reached...")
    # Pre-allocate a list to store all new edges
    additional_edges = []
    
    for frm, to in searches:
        path = np.random.randint(0, nodes, size=max_path_len-2)
        additional_edges.append([frm, path[0]])
        additional_edges.append([path[-1], to])
        additional_edges.extend(np.column_stack((path[:-1], path[1:])))
    
    edges = np.vstack((edges, additional_edges))
    
    print(f"writing {len(edges)} edges to {args.edgelist_output}")
    with open(args.edgelist_output, 'w') as f:
        for edge in edges:
            f.write(f"{edge[0]},{edge[1]}\n")
    
    print(f"writing {len(searches)} search pairs to {args.searchlist_output}")
    with open(args.searchlist_output, 'w') as f:
        for search in searches:
            f.write(f"{search[0]},{search[1]}\n")

if __name__ == '__main__':
    main()
