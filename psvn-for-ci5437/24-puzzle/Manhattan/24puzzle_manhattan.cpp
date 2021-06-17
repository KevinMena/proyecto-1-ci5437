#include "../../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    ManhattanHeuristic24puzzle* mh = new ManhattanHeuristic24puzzle;
    return mh;
}