import numpy as np
from scipy.spatial import KDTree

def add_pair(p, gs):
	found = [ix for ix, g in enumerate(gs) if any(_ in g for _ in p)]
	if len(found) == 0:
		gs.append(set(p))
	elif len(found) == 1:
		gs[found[0]] |= set(p)
	else:
		gs[found[0]] |= gs[found[1]] | set(p)
		gs.pop(found[1])

data = np.loadtxt("input.txt", delimiter=',')
tree = KDTree(data)
N = 1000

# find point pairs that are reasonably close
r = 0.1
while True:
	pairs = tree.query_pairs(r)
	if len(pairs) == data.shape[0]:
		break
	if len(pairs) < 10 * N:
		r *= 1.25
	else:
		break

dist = [(_, np.linalg.norm(data[_[0]] - data[_[1]])) for _ in pairs]
dist = sorted(dist, key=lambda x: x[1])

# find and make groups
groups = []
part1, part2 = 0, 0
for ix, pair in enumerate(dist):
	add_pair(pair[0], groups)
	if ix == N - 1:
		n_circs = sorted([len(_) for _ in groups], reverse=True)
		part1 = np.prod(n_circs[:3])
	if len(groups) == 1 and len(groups[0]) == data.shape[0]:
		part2 = int(data[pair[0][0], 0] * data[pair[0][1], 0])
	if part1 and part2:
		break

print(part1, part2)
