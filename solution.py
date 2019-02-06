#!/usr/bin/python
import sys

class endpoint():
    def __init__(self, ping_dc):
        self.ping_dc = ping_dc
        self.cache_servs = dict()#cache_id : cache_ping

class req():
    def __init__(self, video_id, ep_id, req_num ):
        self.video_id = video_id
        self.ep_id = ep_id
        self.req_num = req_num

def ABreadline(f):
    return [int(x) for x in next(f).split()]

with open(sys.argv[1]) as f:
    vid_num, ep_num, req_num, cache_num,cache_size  = ABreadline(f)
    video_sizes = ABreadline(f)
    endpoints = []
    reqs = []

    for i in range(ep_num):
        ping_dc, ep_cache_num = [int(x) for x in next(f).split()]
        endpoints.append(endpoint(ping_dc))
        for j in range(ep_cache_num):
            cs_id, cs_ping = ABreadline(f)
            endpoints[-1].cache_servs[cs_id] = cs_ping

    for i in range(req_num):
        reqs.append(req(*ABreadline(f)))
            
print([(i.ping_dc, i.cache_servs) for i in endpoints])
