#include "priority_queue.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include "heuristic.hpp"
using namespace std;
using namespace std::chrono;

#define  MAX_LINE_LENGTH 999

int a_star(state_t start, state_t goal, Heuristic* heuristic)
{
    state_t state, child;
    int g, ruleid;
    ruleid_iterator_t iter;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *cost_so_far = new_state_map(); // contains the cost-to-goal for all states that have been generated

    state_map_add(cost_so_far, &start, 0); // Add to the map the first state
    open.Add(0, 0, start); // Add to the priority queue the first state

    g = 0;
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
                int h = heuristic->value(child);
                int priority = new_cost + h;
                open.Add(priority, new_cost, child);
            }
        }
    }

    return -1;
}

int main(int argc, char **argv) 
{
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t initial, goal;

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

    read_state("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 B", &goal);

    int heuristic_choice;
    cout << "Which heuristic to use:" << endl;
    cout << "1. Manhattan Distance:" << endl;
    cout << "2. APDB" << endl;
    cin >> heuristic_choice;

    auto start = high_resolution_clock::now();

    switch (heuristic_choice)
    {
    case 1:
        ManhattanHeuristic heuristic;
        heuristic.load_pdb();
        a_star(initial, goal, &heuristic);
        break;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;     
    return 0;
}
