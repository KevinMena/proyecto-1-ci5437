#include <vector>
#include <algorithm>
#include "priority_queue.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;

#define  MAX_LINE_LENGTH 999 

state_t state, goal;
vector<char*> path;

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

pair<bool, int> f_bounded_visit(int bound, int g_value)
{
    int h = manhattan_distance(state, goal, 16);
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

        if(manhattan_distance(state, goal, 16) < INT32_MAX)
        {
            char str[MAX_LINE_LENGTH + 1];
            sprint_state(str, MAX_LINE_LENGTH + 1, &state);
            path.push_back(str);
            pair<bool, int> pair_value = f_bounded_visit(bound, cost);

            if(pair_value.first) return pair_value;
            t = std::min(t, pair_value.second);
            path.pop_back();
        }
    }

    return make_pair(false, t);
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

    auto start = high_resolution_clock::now();

    read_state("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 B", &goal);
    int bound = manhattan_distance(state, goal, 16);

    while (true)
    {
        pair<bool, int> pair_value = f_bounded_visit(bound, 0);

        if(pair_value.first) break;
        bound = pair_value.second;
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

