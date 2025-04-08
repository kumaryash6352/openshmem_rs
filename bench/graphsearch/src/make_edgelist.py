#!/usr/bin/env python3

from math import ceil
from random import randint as rand
import random
from typing import Iterable, Tuple, List

random.seed("seedforreproducability")

nodes = 16384
n_searches = 256
max_path_len = 128
n_edges = ceil(pow(nodes, 2) / 4) # about 1/4th of nodes have a

print(f"generating {n_edges} edges...")
edges = [(rand(0, nodes - 1), rand(0, nodes - 1)) for _ in range(n_edges)]

def tuple_windows(xs: List[int]) -> Iterable[Tuple[int, int]]:
    for i in range(len(xs) - 1):
        yield (xs[i], xs[i + 1])

def ensure_search_path(frm, to):
    path = [rand(0, nodes - 1) for _ in range(max_path_len - 2)]
    edges.append((frm, path[0]))
    edges.append((path[len(path) - 1], to))
    edges.extend(tuple_windows(path))


print(f"generating {n_searches} search pairs...")
searches = [(rand(0, nodes - 1), rand(0, nodes - 1)) for _ in range(n_searches)]
print(f"ensuring search pairs can be reached...")
[ensure_search_path(x, y) for x, y in searches]

print(f"writing {len(edges)} edges to edgelist")
with open("edgelist", "w") as f:
    for frm, to in edges:
        f.write(f"{frm},{to}\n")

print(f"writing {len(searches)} search pairs to searchlist")
with open("searchlist", "w") as f:
    for frm, to in searches:
        f.write(f"{frm},{to}\n")
