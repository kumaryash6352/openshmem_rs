#!/usr/bin/env python3

#!/usr/bin/env python3

from math import ceil
import numpy as np

np.random.seed(42)

nodes = 65536 * 2
n_searches = 512
max_path_len = 512
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

with open('edgelist', 'w') as f:
    for edge in edges:
        f.write(f"{edge[0]},{edge[1]}\n")

print(f"writing {len(searches)} search pairs to searchlist")
with open('searchlist', 'w') as f:
    for search in searches:
        f.write(f"{search[0]},{search[1]}\n")
