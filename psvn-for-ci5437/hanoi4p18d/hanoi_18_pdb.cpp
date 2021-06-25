#include "../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    MaxHeuristicHanoi* mh = new MaxHeuristicHanoi;
    return mh;
}