#include "priority_queue.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;

#define  MAX_LINE_LENGTH 999 

unsigned mtable[16][16];

void load_pdb(){
	unsigned tmp_table[16][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
								{0,1,2,3,1,2,3,4,3,2,3,4,4,3,4,5},
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
								{6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}};

	for (int i=0; i<16; i++) {
		for (int j=0; j<16; j++) {
			mtable[i][j] = tmp_table[i][j];
		}
	}
}

int manhattan_distance(state_t state, state_t goal, const int max_size)
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

int main(int argc, char **argv) 
{
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t initial, state, child, goal;
    int g, ruleid;
    ruleid_iterator_t iter;

    load_pdb();

    // Read first state of the examples txt to test
    ifstream current_file;
    current_file.open("../benchmarks/15puzzle/test.txt");
    current_file.getline(str, MAX_LINE_LENGTH + 1);
    current_file.close();

    // CONVERT THE STRING TO A STATE
    nchars = read_state(str, &initial);
    if( nchars <= 0 ) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }

    printf("The state you entered is: ");
    print_state(stdout, &initial);
    printf("\n");

    auto start = high_resolution_clock::now();

    copy_state(&state, &initial);

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *cost_so_far = new_state_map(); // contains the cost-to-goal for all states that have been generated

    read_state("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 B", &goal);
    state_map_add(cost_so_far, &state, 0); // Add to the map the first state
    open.Add(manhattan_distance(state, goal, 16), 0, state); // Add to the priority queue the first state

    while( !open.Empty() ) 
    {
        g = open.CurrentPriority();
        
        // remove top state from priority state
        state = open.Top();
        open.Pop();

        // print the distance then the state
        printf("%d  ",g);
        print_state(stdout,&state);
        printf(" \n");

        const int *old_cost = state_map_get(cost_so_far, &state);
        if( (old_cost == NULL) ||  (g < *old_cost) || (!compare_states(&state, &initial)) )
        {
            state_map_add(cost_so_far, &state, g);

            if (is_goal(&state)) break;

            // look at all predecessors of the state
            init_fwd_iter(&iter, &state);
            while( (ruleid = next_ruleid(&iter) ) >= 0 ) 
            {
                apply_fwd_rule(ruleid, &state, &child);
                const int new_cost = g + get_fwd_rule_cost(ruleid);

                int priority = new_cost + manhattan_distance(child, goal, 16);

                if (priority - new_cost < INT32_MAX)
                {
                    open.Add(priority, new_cost, child);
                }
            }
        }
    } 

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;   
    return 0;
}

