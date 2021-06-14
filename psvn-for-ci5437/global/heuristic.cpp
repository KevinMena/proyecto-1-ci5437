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