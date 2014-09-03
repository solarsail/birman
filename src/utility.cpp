#include <cassert>
#include "utility.hpp"

Direction::Direction() : _code(0) { }

Direction::Direction(unsigned char c) : _code(c) { }

Direction::operator unsigned char()
{
    return _code;
}

void Direction::setNS(char d)
{
    assert(d > -2 && d < 2);
    if (_ns != d) _ns += d;
}

void Direction::setWE(char d)
{
    assert(d > -2 && d < 2);
    if (_we != d) _we += d;
}

unsigned char Direction::code() const
{
    return _code;
}

char Direction::NS() const
{
    return _ns;
}

char Direction::WE() const
{
    return _we;
}

float util::invSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf*x*x);
    return x;
}
