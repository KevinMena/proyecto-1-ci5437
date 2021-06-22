#include "heuristic.hpp"

Heuristic::~Heuristic() {}
ManhattanHeuristic::~ManhattanHeuristic() {}

void ManhattanHeuristic::load_pdb()
{
    unsigned tmp_table[16][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,1,2,3,1,2,3,4,2,3,4,5,3,4,5,6},
                            {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
                            {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
                            {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
                            {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
                            {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
                            {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
                            {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
                            {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
                            {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
                            {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
                            {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
                            {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
                            {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
                            {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
                            };

	for (int i=0; i<16; i++) {
		for (int j=0; j<16; j++) {
			mtable[i][j] = tmp_table[i][j];
		}
	}
};

int ManhattanHeuristic::value(state_t state)
{
    int mhd=0;
	for (int i=0; i<16; i++){
		mhd += mtable[state.vars[i]][i];
	}

    return mhd;
}

Puzzle15PDBHeuristic::~Puzzle15PDBHeuristic()
{
    destroy_state_map(map1);
    destroy_state_map(map2);
    destroy_state_map(map3);
    destroy_abstraction(abs1);
    destroy_abstraction(abs2);
    destroy_abstraction(abs3);
}

void Puzzle15PDBHeuristic::load_pdb()
{
    FILE *f1 = fopen("abst_1.pdb","r");
	FILE *f2 = fopen("abst_2.pdb","r");
	FILE *f3 = fopen("abst_3.pdb","r");

	abs1 = read_abstraction_from_file("abst_1.abst");
	map1 = read_state_map(f1);

	abs2 = read_abstraction_from_file("abst_2.abst");
	map2 = read_state_map(f2);

	abs3 = read_abstraction_from_file("abst_3.abst");
	map3 = read_state_map(f3);

	fclose(f1);
	fclose(f2);
	fclose(f3);	
}

int Puzzle15PDBHeuristic::value(state_t state)
{
    abstract_state(abs1, &state, &abs_state1);
	abstract_state(abs2, &state, &abs_state2);
	abstract_state(abs3, &state, &abs_state3);

	sum = *state_map_get(map1, &abs_state1) + *state_map_get(map2, &abs_state2) + *state_map_get(map3, &abs_state3);

	return (sum);
}

Puzzle24PDBHeuristic::~Puzzle24PDBHeuristic()
{
    destroy_state_map(map1);
    destroy_state_map(map2);
    destroy_state_map(map3);
    destroy_state_map(map4);
    destroy_abstraction(abs1);
    destroy_abstraction(abs2);
    destroy_abstraction(abs3);
    destroy_abstraction(abs4);
}

void Puzzle24PDBHeuristic::load_pdb()
{
    FILE *f1 = fopen("abst_1.pdb","r");
	FILE *f2 = fopen("abst_2.pdb","r");
	FILE *f3 = fopen("abst_3.pdb","r");
	FILE *f4 = fopen("abst_4.pdb","r");

	abs1 = read_abstraction_from_file("abst_1.abst");
	map1 = read_state_map(f1);

	abs2 = read_abstraction_from_file("abst_2.abst");
	map2 = read_state_map(f2);

	abs3 = read_abstraction_from_file("abst_3.abst");
	map3 = read_state_map(f3);

	abs4 = read_abstraction_from_file("abst_4.abst");
	map4 = read_state_map(f4);

	fclose(f1);
	fclose(f2);
	fclose(f3);	
	fclose(f4);	
}

int Puzzle24PDBHeuristic::value(state_t state)
{
    abstract_state(abs1, &state, &abs_state1);
	abstract_state(abs2, &state, &abs_state2);
	abstract_state(abs3, &state, &abs_state3);
    abstract_state(abs4, &state, &abs_state4);

	sum = *state_map_get(map1, &abs_state1) + *state_map_get(map2, &abs_state2) + *state_map_get(map3, &abs_state3) + *state_map_get(map4, &abs_state4);

	return (sum);
}

TopSpin12_4Heuristic::~TopSpin12_4Heuristic()
{
    destroy_state_map(map1);
    destroy_state_map(map2);
    destroy_state_map(map3);
    destroy_abstraction(abs1);
    destroy_abstraction(abs2);
    destroy_abstraction(abs3);
}

void TopSpin12_4Heuristic::load_pdb()
{
    FILE *f1 = fopen("abst_1.pdb","r");
	FILE *f2 = fopen("abst_2.pdb","r");
	FILE *f3 = fopen("abst_3.pdb","r");

	abs1 = read_abstraction_from_file("abst_1.abst");
	map1 = read_state_map(f1);

	abs2 = read_abstraction_from_file("abst_2.abst");
	map2 = read_state_map(f2);

	abs3 = read_abstraction_from_file("abst_3.abst");
	map3 = read_state_map(f3);

	fclose(f1);
	fclose(f2);
	fclose(f3);	
}

int TopSpin12_4Heuristic::value(state_t state)
{
    abstract_state(abs1, &state, &abs_state1);
	abstract_state(abs2, &state, &abs_state2);
	abstract_state(abs3, &state, &abs_state3);

	sum = std::max(*state_map_get(map1, &abs_state1), std::max(*state_map_get(map2, &abs_state2), *state_map_get(map3, &abs_state3)));

	return (sum);
}