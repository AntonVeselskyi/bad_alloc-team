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


def score(photo1: Photo, photo2: Photo):
    return min(len(photo1.tags - photo2.tags), len(photo2.tags - photo1.tags), len(photo1.tags & photo2.tags))


def ABreadline(f):
    return [int(x) for x in next(f).split()]

sys.argv.append('a_example.txt')
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
    sys.stdout.flush()
    print("W hi MMMMMMMMMMMMMMMMMMMMMMMMMMM")
    print(datetime.datetime.now())
    sys.stdout.flush()
    gg = sorted(photos)
    print(datetime.datetime.now())
    sys.stdout.flush()
    res = [photos[0]]
    del photos[0]
    l = len(photos)
    for i in photos[:]:
        max_score_for_i = 0
        print(f"{i.id} in {l} proceeded")
        before = datetime.datetime.now()
        best_second_photo = max(photos[:], key=lambda p: score(i, p))

        res.append(best_second_photo)
        photos.remove(best_second_photo)

    fr = open("./res.txt", "w+")
    fr.write(str(len(res)) + "\n")

    fr.write("\n".join((str(i) for i in res)))
    fr.close()
