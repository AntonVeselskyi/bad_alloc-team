#!/usr/bin/python
import sys

class endpoint():
    def __init__(self, ping_dc):
        self.ping_dc = ping_dc
        self.cache_servs = dict() #cache_id : cache_ping
        self.sorted_cache_servs = []

class req():
    def __init__(self, video_id, ep_id, req_num ):
        self.video_id = video_id
        self.ep_id = ep_id
        self.req_num = req_num

def ABreadline(f):
    return [int(x) for x in next(f).split()]

if(len(sys.argv) == 1):
    sys.argv.append('input/me_at_the_zoo.in')

with open(sys.argv[1]) as f:
    vid_num, ep_num, req_num, cache_num,cache_size  = ABreadline(f)
    video_sizes = ABreadline(f)
    endpoints = []
    reqs = []
    #print(vid_num, cache_num)

    for i in range(ep_num):
        ping_dc, ep_cache_num = [int(x) for x in next(f).split()]
        endpoints.append(endpoint(ping_dc))
        for j in range(ep_cache_num):
            cs_id, cs_ping = ABreadline(f)
            endpoints[-1].cache_servs[cs_id] = cs_ping

    for i in range(req_num):
        reqs.append(req(*ABreadline(f)))

    #descending sort for reqs(we need process most popular videos first)
    reqs.sort(key=lambda rq: rq.req_num, reverse=True)
    #print([i.req_num for i in reqs])


#yeahoo we have the inputs

#find the best cache servers for every EP
# (sort the list of servers)

for ep in endpoints:
    list_sort = list(ep.cache_servs.items())
    #print(list_sort)
    list_sort.sort(key=lambda ep: ep[1])
    #print([i[1] for i in list_sort])
    #print(list_sort)
    ep.sorted_cache_servs = list_sort


cache_list = [cache_size] * cache_num

res = dict()
for r in reqs:
    c = endpoints[r.ep_id].cache_servs
    for i in endpoints[r.ep_id].sorted_cache_servs:
        if cache_list[i[0]] > video_sizes[r.video_id] :
            cache_list[i[0]] -= video_sizes[r.video_id]
            if not res.get(i[0]):
                res[i[0]] = [r.video_id]
            elif r.video_id not in res[i[0]]:
                res[i[0]].append(r.video_id)

fr = open("./res.txt","w+")
fr.write(str(len(res))+"\n")
for server, videos in res.items():
    fr.write(str(server)+" "+" ".join(str(x) for x in videos)+"\n")
fr.close()