#include "../../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    Puzzle24PDBHeuristic* mh = new Puzzle24PDBHeuristic;
    return mh;
}