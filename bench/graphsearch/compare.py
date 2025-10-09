#!/usr/bin/env python3

import subprocess
import csv
import os
import argparse
from pathlib import Path

runner_base = ["mpiexec.hydra", "-bind-to", "hwthread"]
cbin = "graphsearch"
rsbin = "graphsearch-rs"
graph_sizes = [pow(x, 3) for x in [4, 8, 16, 32, 64]]  # N×N graph sizes to test
pe_counts = [1, 2, 4, 8, 16]  # PE counts to test for fixed problem size
fixed_graph_size = 32**3  # fixed graph size for PE scaling tests
n_searches = 64  # number of search pairs per test

def run_command(cmd):
    try:
        print(f"running: {' '.join(cmd)}")
        result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, 
                              universal_newlines=True, check=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"command failed: {e}")
        print(f"stderr: {e.stderr}")
        return None
    except subprocess.TimeoutExpired:
        print("command timed out")
        return None

def extract_searches_per_second(output):
    if output is None:
        return None
    try:
        lines = output.strip().split('\n')
        return float(lines[-1])
    except (ValueError, IndexError):
        print(f"could not parse output: {output}")
        return None

def generate_test_data(nodes, searches, temp_dir):
    edgelist_path = temp_dir / "edgelist"
    searchlist_path = temp_dir / "searchlist"
    
    make_edgelist_cmd = [
        "python3", "bench/graphsearch/src/make_edgelist.py",
        "--nodes", str(nodes),
        "--n-searches", str(searches),
        "--edgelist-output", str(edgelist_path),
        "--searchlist-output", str(searchlist_path)
    ]
    
    if run_command(make_edgelist_cmd) is None:
        return None, None
    
    return str(searchlist_path), str(edgelist_path)

def run_benchmark(binary, searchlist, edgelist, pe_count=2):
    runner = [*runner_base, "-n", str(pe_count)]
    cmd = [*runner, binary, searchlist, edgelist]
    output = run_command(cmd)
    return extract_searches_per_second(output)

def run_pe_scaling_benchmark(temp_path):
    print(f"\n=== PE SCALING TEST (fixed graph size: {fixed_graph_size}×{fixed_graph_size}) ===")
    
    results = []
    
    searchlist, edgelist = generate_test_data(fixed_graph_size, n_searches, temp_path)
    if searchlist is None:
        print(f"failed to generate test data for size {fixed_graph_size}")
        return results
    
    for pe_count in pe_counts:
        print(f"\ntesting with {pe_count} PE(s)...")
        
        print(f"running rs implementation with {pe_count} PE(s)...")
        rs_sps = run_benchmark(rsbin, searchlist, edgelist, pe_count)
        
        print(f"running c implementation with {pe_count} PE(s)...")
        c_sps = run_benchmark(cbin, searchlist, edgelist, pe_count)
        
        if rs_sps is not None and c_sps is not None:
            results.append([pe_count, rs_sps, c_sps])
            print(f"results - RS: {rs_sps:.3f} searches/sec, C: {c_sps:.3f} searches/sec")
        else:
            print(f"failed to get valid results for {pe_count} PE(s)")
    
    return results

def run_graph_size_benchmark(temp_path):
    print(f"\n=== GRAPH SIZE SCALING TEST (fixed PE count: 2) ===")
    
    results = []
    
    for graph_size in graph_sizes:
        print(f"\ntesting graph size: {graph_size}×{graph_size}")
        
        searchlist, edgelist = generate_test_data(graph_size, n_searches, temp_path)
        if searchlist is None:
            print(f"failed to generate test data for size {graph_size}")
            continue
        
        print("running rs implementation...")
        rs_sps = run_benchmark(rsbin, searchlist, edgelist, 2)
        
        print("running c implementation...")
        c_sps = run_benchmark(cbin, searchlist, edgelist, 2)
        
        if rs_sps is not None and c_sps is not None:
            results.append([f"{graph_size}x{graph_size}", rs_sps, c_sps])
            print(f"results - RS: {rs_sps:.3f} searches/sec, C: {c_sps:.3f} searches/sec")
        else:
            print(f"failed to get valid results for size {graph_size}")
    
    return results

def main():
    parser = argparse.ArgumentParser(description="graph search implementations")
    parser.add_argument("--mode", choices=["graph-size", "pe-scaling", "both"], 
                       default="both", help="benchmark mode to run")
    parser.add_argument("--output-dir", default="/tmp/results", 
                       help="directory to write results CSV files")
    
    args = parser.parse_args()
    
    os.makedirs(args.output_dir, exist_ok=True)
    
    # create temp directory for test files under working directory
    temp_path = Path("./bench/graphsearch/temp_data")
    temp_path.mkdir(exist_ok=True, parents=True)
    
    try:
        if args.mode in ["graph-size", "both"]:
            print("Running graph size scaling benchmark...")
            graph_size_results = run_graph_size_benchmark(temp_path)
            
            # Write graph size results
            csv_path = Path(args.output_dir) / "bfs_graph_size.csv"
            with open(csv_path, "w", newline="") as f:
                writer = csv.writer(f)
                writer.writerow(["graph size (NxN)", "RS (searches/second)", "C (searches/second)"])
                writer.writerows(graph_size_results)
            
            print(f"\nGraph size results written to {csv_path}")
            print("\nGraph size summary:")
            for row in graph_size_results:
                print(f"  {row[0]}: RS={row[1]:.3f}, C={row[2]:.3f}")
        
        if args.mode in ["pe-scaling", "both"]:
            print("\nRunning PE scaling benchmark...")
            pe_scaling_results = run_pe_scaling_benchmark(temp_path)
            
            # Write PE scaling results
            csv_path = Path(args.output_dir) / "bfs_pe_scaling.csv"
            with open(csv_path, "w", newline="") as f:
                writer = csv.writer(f)
                writer.writerow(["PE count", "RS (searches/second)", "C (searches/second)"])
                writer.writerows(pe_scaling_results)
            
            print(f"\nPE scaling results written to {csv_path}")
            print("\nPE scaling summary:")
            for row in pe_scaling_results:
                print(f"  {row[0]} PE(s): RS={row[1]:.3f}, C={row[2]:.3f}")
    
    finally:
        # cleanup temp directory
        import shutil
        if temp_path.exists():
            shutil.rmtree(temp_path)

if __name__ == '__main__':
    main()
