#ifndef _HEURISTIC_HPP
#define _HEURISTIC_HPP

#include <iostream>

class Heuristic
{
public:
    virtual void load_pdb() = 0;
    virtual int value(state_t state) = 0;
};

class ManhattanHeuristic : public Heuristic
{
public:
    int mtable[16][16];

    void load_pdb();
    int value(state_t state);
};

class Puzzle15PDBHeuristic : public Heuristic
{
public:
    int sum;
    void load_pdb();
    int value(state_t state);
private:
    state_map_t *map1;
    state_map_t *map2;
    state_map_t *map3;
    abstraction_t *abs1;
    abstraction_t *abs2;
    abstraction_t *abs3;
    state_t abs_state1;
    state_t abs_state2;
    state_t abs_state3;
};

#endif