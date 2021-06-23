#include "../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    TopSpin12_4Heuristic* mh = new TopSpin12_4Heuristic;
    return mh;
}