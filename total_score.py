#!/usr/bin/python

import sys


class endpoint():
    def __init__(self, ping_dc):
        self.ping_dc = ping_dc
        self.cache_servs = dict()  # cache_id : cache_ping


class req():
    def __init__(self, video_id, ep_id, req_num):
        self.video_id = video_id
        self.ep_id = ep_id
        self.req_num = req_num
        self.max_value = 0;


def ABreadline(f):
    return [int(x) for x in next(f).split()]


with open(sys.argv[1]) as f:
    vid_num, ep_num, req_num, cache_num, cache_size = ABreadline(f)
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

with open(sys.argv[2]) as f:
    cache_num = int(next(f))
    for line in f.readlines():
        c_id, videos = line.split(maxsplit=1)
        c_id = int(c_id)
        for video_id in [int(i) for i in videos.split()]:
            for r in reqs:
                profit = (endpoints[r.ep_id].ping_dc - endpoints[r.ep_id].cache_servs[c_id]) if c_id in endpoints[
                    r.ep_id].cache_servs else 0
                if r.video_id == video_id and r.max_value < profit:
                    r.max_value = profit

print(sum(r.max_value * r.req_num for r in reqs) / float(sum(r.req_num for r in reqs)) * 1000)
