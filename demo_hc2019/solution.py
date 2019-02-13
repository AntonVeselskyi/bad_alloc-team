#!/usr/bin/python
import sys



def ABreadline(f):
    return [int(x) for x in next(f).split()]


with open(sys.argv[1]) as f:
    vid_num, ep_num, req_num, cache_num,cache_size  = ABreadline(f)
