#include "../../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    ManhattanHeuristic* mh = new ManhattanHeuristic;
    return mh;
}