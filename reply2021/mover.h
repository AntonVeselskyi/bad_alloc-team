//
// Created by Borys on 3/11/2021.
//

#ifndef DEMO_HC2021_MOVER_H
#define DEMO_HC2021_MOVER_H

#include "entities.h"

void move_antenna_from_border(Antenna &antenna, size_t width, size_t height)
{
    size_t max_left_dist = antenna.x;
    size_t max_right_dist = width - antenna.x;
    size_t max_top_dist = antenna.y;
    size_t max_bottom_dist = height - antenna.y;

    size_t bottom_shift = 0;
    size_t top_shift = 0;
    size_t left_shift = 0;
    size_t right_shift = 0;

    if (antenna.range > max_bottom_dist) {
        bottom_shift = antenna.range - max_bottom_dist;
    }
    if (antenna.range > max_top_dist) {
        top_shift = antenna.range - max_top_dist;
    }
    if (antenna.range > max_right_dist) {
        right_shift = antenna.range - max_right_dist;
    }
    if (antenna.range > max_left_dist) {
        left_shift = antenna.range - max_left_dist;
    }

    if (left_shift && bottom_shift) {
        size_t res_shift_koef = left_shift / bottom_shift;
        size_t real_left_shift = left_shift * res_shift_koef;
        antenna.x += real_left_shift;
        antenna.y -= antenna.range - real_left_shift;
    } else if (left_shift && top_shift) {
        size_t res_shift_koef = left_shift / top_shift;
        size_t real_left_shift = left_shift * res_shift_koef;
        antenna.x += real_left_shift;
        antenna.y += antenna.range - real_left_shift;
    } else if (right_shift && bottom_shift) {
        size_t res_shift_koef = right_shift / bottom_shift;
        size_t real_right_shift = left_shift * res_shift_koef;
        antenna.x -= real_right_shift;
        antenna.y -= antenna.range - real_right_shift;
    } else if (right_shift && top_shift) {
        size_t res_shift_koef = right_shift / top_shift;
        size_t real_right_shift = right_shift * res_shift_koef;
        antenna.x -= res_shift_koef;
        antenna.y += antenna.range - real_right_shift;
    } else if (right_shift) {
        antenna.x -= right_shift;
    } else if (left_shift) {
        antenna.x += left_shift;
    } else if (top_shift) {
        antenna.y += top_shift;
    } else if (bottom_shift) {
        antenna.y -= bottom_shift;
    }
}

#endif //DEMO_HC2021_MOVER_H
