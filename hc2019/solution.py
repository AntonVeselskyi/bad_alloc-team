#!/usr/bin/python
import sys
import datetime
from enum import Enum


class Photo:

    def __init__(self, id, orie, tags):
        self.id = id
        self.orient = orie
        self.tags = tags

    def __eq__(self, other):
        return self.id == other.id

    def __lt__(self, other):
        return len(self.tags) < len(other.tags)


def score(photo1: Photo, photo2: Photo):
    return min(len(photo1.tags - photo2.tags), len(photo2.tags - photo1.tags), len(photo1.tags & photo2.tags))


def ABreadline(f):
    return [int(x) for x in next(f).split()]

#sys.argv.append('a_example.txt')
with open(sys.argv[1]) as f:
    N = ABreadline(f)[0]
    photos = []
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
        photos.append(Photo(photo_num, orient, tags))

    # Manager

    photos = sorted(photos)

    chunck = int(N/30) + 2;
    res = [photos[0]]
    del photos[0]
    print(N)
    for n in range(len(photos[:])-1):
        #print("progress", n)
        max_score_for_i = 0
        best_second_photo = max(photos[:chunck if chunck < len(photos) else len(photos)-1 ], key=lambda p: score(res[-1], p))

        res.append(best_second_photo)
        photos.remove(best_second_photo)

    res.append(photos[-1])
    fr = open("./res.txt", "w+")
    fr.write(str(len(res)) + "\n")
    fr.write("".join((str(i.id)+'\n' for i in res)))
    fr.close()
