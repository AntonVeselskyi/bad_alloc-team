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


