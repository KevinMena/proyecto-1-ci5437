#ifndef _HEURISTIC_HPP
#define _HEURISTIC_HPP

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

// class PDBHeuristic : public Heuristic
// {
//     void load_pdb();
//     int heuristic(state_t state);
// };

#endif