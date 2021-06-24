#include "../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    MaxHeuristic* mh = new MaxHeuristic;
    return mh;
}