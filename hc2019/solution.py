#!/usr/bin/python
import sys
from enum import Enum


class Photo:

    def __init__(self, id, orie, tags):
        self.id = id
        self.orient = orie
        self.tags = tags


def score(photo1: Photo, photo2: Photo):
    return min(len(photo1.tags - photo2.tags), len(photo2.tags - photo1.tags), len(photo1.tags & photo2.tags))


def ABreadline(f):
    return [int(x) for x in next(f).split()]


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

    for ph in photos:
        print(ph.orient, ph.tags)
