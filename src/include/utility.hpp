#pragma once

struct Direction {
    unsigned char up;
    unsigned char down;
    unsigned char left;
    unsigned char right;

    Direction() :
        up(0), down(0), left(0), right(0)
    { }
};
