#!/usr/bin/python
import sys
from enum import Enum



def ABreadline(f):
    return [int(x) for x in next(f).split()]

def ABread_by_char(bs):
        bs= []
        for _ in range(N):
            bs.append( int(f.read(1)) )
        f.read(1) # skip '\n'
        return bs;

with open(sys.argv[1]) as f:
    rows, columns, min_per_slice, max_cells = ABreadline(f)
