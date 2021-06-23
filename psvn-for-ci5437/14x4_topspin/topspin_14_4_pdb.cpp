#include "../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    TopSpin14_4Heuristic* mh = new TopSpin14_4Heuristic;
    return mh;
}