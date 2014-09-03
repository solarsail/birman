#pragma once

class Direction {
    public:
        typedef unsigned char CodeType;

        static const unsigned char NORTH = 0xF0;
        static const unsigned char SOUTH = 0x10;
        static const unsigned char WEST  = 0x0F;
        static const unsigned char EAST  = 0x01;
        static const unsigned char NE    = 0xF1;
        static const unsigned char SE    = 0x11;
        static const unsigned char NW    = 0xFF;
        static const unsigned char SW    = 0x1F;

        Direction();
        Direction(unsigned char d);
        operator unsigned char();

        void setNS(char d);
        void setWE(char d);
        char NS() const;
        char WE() const;
        unsigned char code() const;

    private:
        union {
            unsigned char _code;
            struct {
                char _we : 4;
                char _ns : 4;
            };
        };
};

enum class AniState {
    Play,
    Pause,
    Stop
};

namespace util {
    float invSqrt(float x);
}
