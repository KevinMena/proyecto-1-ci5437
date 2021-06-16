#include "priority_queue.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using namespace std::chrono;

#define  MAX_LINE_LENGTH 999

int64_t nodes;

int a_star(state_t start, Heuristic* heuristic)
{
    state_t state, child;
    int g, ruleid;
    ruleid_iterator_t iter;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *cost_so_far = new_state_map(); // contains the cost-to-goal for all states that have been generated

    state_map_add(cost_so_far, &start, 0); // Add to the map the first state
    open.Add(heuristic->value(start), 0, start); // Add to the priority queue the first state

    while( !open.Empty() ) 
    {
        g = open.CurrentPriority();
        
        // remove top state from priority state
        state = open.Top();
        open.Pop();

        int *old_cost = state_map_get(cost_so_far, &state);
        nodes++;
        
        if( (old_cost == NULL) ||  (g < *old_cost) || (!compare_states(&state, &start)) )
        {
            state_map_add(cost_so_far, &state, g);

            if (is_goal(&state)) 
            {
                destroy_state_map(cost_so_far);
                open.Clear();
                return g;
            }

            // look at all predecessors of the state
            init_fwd_iter(&iter, &state);
            while( (ruleid = next_ruleid(&iter) ) >= 0 ) 
            {
                apply_fwd_rule(ruleid, &state, &child);
                const int new_cost = g + get_fwd_rule_cost(ruleid);

                int h = heuristic->value(child);

                int priority = new_cost + h;

                if (h < INT32_MAX)
                {
                    open.Add(priority, new_cost, child);
                }
            }
        }
    }

    return -1;
}

int main(int argc, char **argv) 
{
    if(argc < 3)
    {
        cout << "Missing arguments. Run with ./<domain>.ida_star <input_file> <output_file>";
    }

    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t state;

    Heuristic* heuristic = load_heuristic();
    heuristic->load_pdb();

    // Read first state of the examples txt to test
    ifstream input_file;
    ofstream output_file;

    input_file.open(argv[1]);

    output_file.open(argv[2]);
    output_file << "Instance    Solved    Time    Nodes-Expanded    Distance\n";
    output_file << "-----------------------------------------------------------------------------\n";

    while(input_file.peek() != EOF)
    {
        input_file.getline(str, MAX_LINE_LENGTH + 1);
        
        // CONVERT THE STRING TO A STATE
        nchars = read_state(str, &state);
        if( nchars <= 0 ) {
            printf("Error: invalid state entered.\n");
            continue;
        }

        printf("Solving state: ");
        print_state(stdout, &state);
        printf("\n");

        nodes = 0;

        auto start = high_resolution_clock::now();

        int goal = a_star(state, heuristic);

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        if(goal != -1)
        {
            output_file << str << "    True    " << duration.count() << "    " << nodes << "    " << goal << endl;
        }
        else
        {
            output_file << str << "    False    NA    NA    NA" << endl;
        }

        input_file.clear();
    }

    input_file.close();
    output_file.close();

    delete heuristic;
    
    return 0;
}

