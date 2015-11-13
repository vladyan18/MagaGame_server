#ifndef NUKESINAIR_H
#define NUKESINAIR_H
#include <deque>

class NukeRocket
{
public:
    int from;
    int to;
    int lifetime;
    int count;
    int explosions;

    NukeRocket(int from = 0, int to = 0, int count = 0, int explosions = 0)
    {
        this->from = from;
        this->to = to;
        this->count = count;
        this->explosions = explosions;
        this->lifetime = 2;
    }

};


#endif // NUKESINAIR_H
