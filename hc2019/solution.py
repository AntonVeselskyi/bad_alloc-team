#!/usr/bin/python
import sys
import datetime
from enum import Enum


class Photo:

    def __init__(self, id, tags):
        self.id = id
        self.tags = tags

    def __eq__(self, other):
        return self.id == other.id

    def __lt__(self, other):
        return len(self.tags) < len(other.tags)

    def __add__(self, other):
        return Photo(str(self.id) + " " + str(other.id), self.tags | other.tags)


def score(photo1: Photo, photo2: Photo):
    return min(len(photo1.tags - photo2.tags), len(photo2.tags - photo1.tags), len(photo1.tags & photo2.tags))


def merge_vertical(verticals: list):
    chunk = int(N / 30) + 3
    res = []
    while len(verticals) - 2 > 3:
        tmp = max(verticals[1:chunk if chunk < len(verticals) else len(verticals) - 1],
                  key=lambda p: score(verticals[0], p))
        res.append(tmp + verticals[0])
        verticals.remove(tmp)
        del verticals[0]

    if(len(res)>=2):
        res.append(verticals[-1] + verticals[-2])
    return res


def ABreadline(f):
    return [int(x) for x in next(f).split()]


# sys.argv.append('a_example.txt')
with open(sys.argv[1]) as f:
    N = ABreadline(f)[0]
    Hphotos = []
    Vphotos = []
    for photo_num in range(N):
        orient = '';
        tags = set()
        for n, word in enumerate(next(f).split()):
            if n == 0:
                orient = str(word)
                continue
            if n == 1:
                continue
            tags.add(word)
        if (orient == 'H'):
            Hphotos.append(Photo(photo_num, tags))
        else:
            Vphotos.append(Photo(photo_num, tags))

    print([v.id for v in Vphotos])
    # Manager

    Vphotos = sorted(Vphotos)
    Hphotos += merge_vertical(Vphotos)
    Hphotos = sorted(Hphotos)

    chunck = int(N / 30) + 2;
    res = [Hphotos[0]]
    del Hphotos[0]
    print(N)
    for n in range(len(Hphotos[:]) - 1):
        #print("progress", n)
        max_score_for_i = 0
        best_second_photo = max(Hphotos[:chunck if chunck < len(Hphotos) else len(Hphotos) - 1],
                                key=lambda p: score(res[-1], p))

        res.append(best_second_photo)
        Hphotos.remove(best_second_photo)

    res.append(Hphotos[-1])
    fr = open("./res.txt", "w+")
    fr.write(str(len(res)) + "\n")
    fr.write("".join((str(i.id) + '\n' for i in res)))
    fr.close()
