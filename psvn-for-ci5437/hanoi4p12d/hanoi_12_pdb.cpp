#include "../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    MaxHeuristicTwo* mh = new MaxHeuristicTwo;
    return mh;
}