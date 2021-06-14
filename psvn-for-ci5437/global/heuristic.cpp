#include "heuristic.hpp"

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
        // int current_state[max_size];
    // int goal_state[max_size];
    // int mhd = 0;
    // for( int i = 0; i < max_size; i++ ) {
    //     current_state[state.vars[ i ]] = i;
    //     goal_state[goal.vars[ i ]] = i;
    // }

    // int half_size = max_size / 4;

    // for( int i = 1; i < max_size; i++ ) {
    //     int first_half = abs((current_state[i] / half_size) - (goal_state[i] / half_size));
    //     int second_half = abs((current_state[i] % half_size) - (goal_state[i] % half_size));
    //     mhd += first_half + second_half;
    // }

    int mhd=0;
	for (int i=0; i<16; i++){
		mhd += mtable[state.vars[i]][i];
	}

    return mhd;
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