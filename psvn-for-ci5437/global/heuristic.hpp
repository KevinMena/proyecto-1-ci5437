#ifndef _HEURISTIC_HPP
#define _HEURISTIC_HPP

#include <iostream>

class Heuristic
{
public:
    Heuristic() { };
    virtual ~Heuristic() = 0;
    virtual void load_pdb() = 0;
    virtual int value(state_t state) = 0;
};

class ManhattanHeuristic : public Heuristic
{
public:
    ManhattanHeuristic() { };
    ~ManhattanHeuristic();
    
    int mtable[16][16];
    void load_pdb();
    int value(state_t state);
};

class Puzzle15PDBHeuristic : public Heuristic
{
public:
    Puzzle15PDBHeuristic() { };
    ~Puzzle15PDBHeuristic();
    
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

class Puzzle24PDBHeuristic : public Heuristic
{
public:
    Puzzle24PDBHeuristic() { };
    ~Puzzle24PDBHeuristic();
    
    int sum;
    void load_pdb();
    int value(state_t state);
private:
    state_map_t *map1;
    state_map_t *map2;
    state_map_t *map3;
    state_map_t *map4;
    state_map_t *map5;
    abstraction_t *abs1;
    abstraction_t *abs2;
    abstraction_t *abs3;
    abstraction_t *abs4;
    abstraction_t *abs5;
    state_t abs_state1;
    state_t abs_state2;
    state_t abs_state3;
    state_t abs_state4;
    state_t abs_state5;
};

class MaxHeuristic : public Heuristic
{
public:
    MaxHeuristic() { };
    ~MaxHeuristic();
    
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