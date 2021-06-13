#include "priority_queue.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stack>
using namespace std;
using namespace std::chrono;

#define  MAX_LINE_LENGTH 999 

int manhattan_distance(state_t state, state_t goal, const int max_size)
{
    int current_state[max_size];
    int goal_state[max_size];
    int mhd = 0;
    for( int i = 0; i < max_size; i++ ) {
        current_state[state.vars[ i ]] = i;
        goal_state[goal.vars[ i ]] = i;
    }

    int half_size = max_size / 4;

    for( int i = 1; i < max_size; i++ ) {
        int first_half = abs((current_state[i] / half_size) - (goal_state[i] / half_size));
        int second_half = abs((current_state[i] % half_size) - (goal_state[i] % half_size));
        mhd += first_half + second_half;
    }

    return mhd;
}

int main(int argc, char **argv) 
{
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t state, child, goal;
    int d, ruleid;
    ruleid_iterator_t iter;

    // Read first state of the examples txt to test
    ifstream current_file;
    current_file.open("../benchmarks/15puzzle/test.txt");
    current_file.getline(str, MAX_LINE_LENGTH + 1);
    current_file.close();

    // CONVERT THE STRING TO A STATE
    nchars = read_state(str, &state);
    if( nchars <= 0 ) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }

    printf("The state you entered is: ");
    print_state(stdout, &state);
    printf("\n");

    auto start = high_resolution_clock::now();

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *cost_so_far = new_state_map(); // contains the cost-to-goal for all states that have been generated

    read_state("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 B", &goal);
    state_map_add(cost_so_far, &state, 0); // Add to the map the first state
    open.Add(0, 0, state); // Add to the priority queue the first state

    d = 0;
    while( !open.Empty() ) 
    {
        d = open.CurrentPriority();
        
        // remove top state from priority state
        state = open.Top();
        open.Pop();

        // print the distance then the state
        printf("%d  ",d);
        print_state(stdout,&state);
        printf(" \n");

        if (is_goal(&state)) break;

        // look at all predecessors of the state
        init_fwd_iter(&iter, &state);
        while( (ruleid = next_ruleid(&iter) ) >= 0 ) 
        {
            apply_fwd_rule(ruleid, &state, &child);
            const int new_cost = (*state_map_get(cost_so_far, &state)) + get_fwd_rule_cost(ruleid);

            const int *old_cost = state_map_get(cost_so_far, &child);
            if( (old_cost == NULL) || (new_cost < *old_cost) )
            {
                state_map_add(cost_so_far, &child, new_cost);
                int priority = new_cost + manhattan_distance(child, goal, 16);
                open.Add(priority, new_cost, child);
            }
        }
    } 

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;     
    return 0;
}

