#pragma once

struct Direction {
    static const unsigned NORTH = 0x01000000;
    static const unsigned SOUTH = 0x00010000;
    static const unsigned EAST  = 0x00000100;
    static const unsigned WEST  = 0x00000001;
    static const unsigned NE    = 0x01000100;
    static const unsigned NW    = 0x01000001;
    static const unsigned SE    = 0x00010100;
    static const unsigned SW    = 0x00010001;

    union {
        unsigned code;
        struct {
            unsigned char west;
            unsigned char east;
            unsigned char south;
            unsigned char north;
        };
    };

    Direction() : code(0) { }
    Direction(unsigned d) : code(d) { }
    operator unsigned() { return code; }
};

enum class AniState {
    Play,
    Pause,
    Stop
};

namespace util {
    float invSqrt(float x);
}
