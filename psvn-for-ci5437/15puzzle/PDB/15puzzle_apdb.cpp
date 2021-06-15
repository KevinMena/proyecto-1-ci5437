#include "../../global/heuristic.cpp"

Heuristic* load_heuristic()
{
    Puzzle15PDBHeuristic* mh = new Puzzle15PDBHeuristic;
    return mh;
}