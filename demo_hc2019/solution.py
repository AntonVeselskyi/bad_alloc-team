#!/usr/bin/python
import sys
from enum import Enum


# 0 - tomato
# 1 - mushroom

class Status(Enum):
    FREE = 1
    TAKEN = 2
    BSTD = 3


class PzCell(int):
    def __init__(self, num, status=Status.FREE):
        super(PzCell, self).__new__(PzCell, num)
        self.status = status


def ABreadline(f):
    return [int(x) for x in next(f).split()]


cells = []
with open(sys.argv[1]) as f:
    rows, columns, min_per_slice, max_cells = ABreadline(f)
    for line in f.readlines():
        cells.append([PzCell(0) if c == 'T' else PzCell(1) for c in line[:-1]])

    i = 0
    j = 1
    slices = []

    while i < rows:
        slice = find_slice(cells, min_per_slice, max_cells, (i, j),
                           next((i for i, v in enumerate(cells[i][j:]) if v.status == Status.TAKEN), default=columns))

        if not slice:
            if j < columns - 1:
                j += 1
            else:
                j = 0
                i += 1
            continue
        slices.append(slice)

        for i in range(slice[1][0], slice[1][1] + 1):
            for j in range(slice[0][0], slice[0][1] + 1):
                cells[i][j].status = Status.TAKEN

        if j < columns - slice[0][1]:
            j += slice[0][1]
        else:
            j = 0
            i += 1

print(slices)