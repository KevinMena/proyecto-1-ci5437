#include <vector>
#include <algorithm>
#include "priority_queue.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include "heuristic.hpp"
using namespace std;
using namespace std::chrono;

#define  MAX_LINE_LENGTH 999 

state_t state;
vector<char*> path;

pair<bool, int> f_bounded_visit(int bound, int g_value, Heuristic* heuristic)
{
    int h = heuristic->value(state);
    int f_value = g_value + h;

    if (f_value > bound) return make_pair(false, f_value);
    if (h == 0) return make_pair(true, g_value);

    int t = INT32_MAX;
    int ruleid;
    ruleid_iterator_t iter;
    state_t state_copy;
    copy_state(&state_copy, &state);
    init_fwd_iter(&iter, &state_copy);
    while( (ruleid = next_ruleid(&iter) ) >= 0 ) 
    {
        apply_fwd_rule(ruleid, &state_copy, &state);
        const int cost = g_value + get_fwd_rule_cost(ruleid);

        if(heuristic->value(state) < INT32_MAX)
        {
            char str[MAX_LINE_LENGTH + 1];
            sprint_state(str, MAX_LINE_LENGTH + 1, &state);
            path.push_back(str);
            pair<bool, int> pair_value = f_bounded_visit(bound, cost, heuristic);

            if(pair_value.first) return pair_value;
            t = std::min(t, pair_value.second);
            path.pop_back();
        }
    }

    return make_pair(false, t);
}

int ida_star(Heuristic* heuristic)
{
    int bound = heuristic->value(state);

    while (true)
    {
        pair<bool, int> pair_value = f_bounded_visit(bound, 0, heuristic);

        if(pair_value.first) return 1;
        bound = pair_value.second;
    }
}

int main(int argc, char **argv) 
{
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars;

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

    //Heuristic* heuristic;
    int heuristic_choice;
    cout << "Which heuristic to use:" << endl;
    cout << "1. Manhattan Distance:" << endl;
    cout << "2. APDB" << endl;
    cin >> heuristic_choice;

    auto start = high_resolution_clock::now();

    switch (heuristic_choice)
    {
        case 1:
        {
            ManhattanHeuristic heuristic;
            heuristic.load_pdb();
            ida_star(&heuristic);
        }
            break;
        case 2:
        {
            Puzzle15PDBHeuristic heuristic;
            heuristic.load_pdb();
            ida_star(&heuristic);
        }
            break;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    for(auto elem : path)
    {
        cout << elem << endl;
    }
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;     
    return 0;
}

