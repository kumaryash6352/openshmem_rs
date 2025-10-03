#!/usr/bin/env python3

import subprocess
import csv
import os
from pathlib import Path

runner = ["mpiexec.hydra", "-n", "2", "-bind-to", "hwthread"]
cbin = "graphsearch"
rsbin = "graphsearch-rs"
graph_sizes = [32, 64, 128, 256, 512]  # N×N graph sizes to test
n_searches = 64  # number of search pairs per test

def run_command(cmd):
    try:
        print(f"running: {' '.join(cmd)}")
        result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, 
                              universal_newlines=True, check=True, timeout=300)
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

def run_benchmark(binary, searchlist, edgelist):
    cmd = [*runner, binary, searchlist, edgelist]
    output = run_command(cmd)
    return extract_searches_per_second(output)

def main():
    os.makedirs("/tmp/results", exist_ok=True)
    
    results = []
    
    # create temp directory for test files under working directory
    temp_path = Path("./bench/graphsearch/temp_data")
    temp_path.mkdir(exist_ok=True)
    
    try:
        for graph_size in graph_sizes:
            print(f"\ntesting graph size: {graph_size}×{graph_size}")
            
            searchlist, edgelist = generate_test_data(graph_size, n_searches, temp_path)
            if searchlist is None:
                print(f"failed to generate test data for size {graph_size}")
                continue
            
            print("running rs implementation...")
            rs_sps = run_benchmark(rsbin, searchlist, edgelist)
            
            print("running c implementation...")
            c_sps = run_benchmark(cbin, searchlist, edgelist)
            
            if rs_sps is not None and c_sps is not None:
                results.append([f"{graph_size}x{graph_size}", rs_sps, c_sps])
                print(f"results - RS: {rs_sps:.3f} searches/sec, C: {c_sps:.3f} searches/sec")
            else:
                print(f"failed to get valid results for size {graph_size}")
    
    finally:
        # cleanup temp directory
        import shutil
        if temp_path.exists():
            shutil.rmtree(temp_path)
    
    csv_path = "/tmp/results/bfs.csv"
    with open(csv_path, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["graph size (NxN)", "RS (searches/second)", "C (searches/second)"])
        writer.writerows(results)
    
    print(f"\nresults written to {csv_path}")
    print("\nsummary:")
    for row in results:
        print(f"  {row[0]}: RS={row[1]:.3f}, C={row[2]:.3f}")

if __name__ == '__main__':
    main()
