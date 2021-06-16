#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;

#define  MAX_LINE_LENGTH 999 

int64_t nodes;

pair<bool, int> f_bounded_visit(int bound, int g_value, state_t state, Heuristic* heuristic, const int history)
{
    int h = heuristic->value(state);
    int f_value = g_value + h;

    if (f_value > bound) return make_pair(false, f_value);
    if (h == 0) return make_pair(true, g_value);

    nodes++;

    int t = INT32_MAX;
    int child_history = 0;
    int ruleid;
    ruleid_iterator_t iter;
    state_t child;

    init_fwd_iter(&iter, &state);
    while( (ruleid = next_ruleid(&iter) ) >= 0 ) 
    {
        if( !fwd_rule_valid_for_history(history, ruleid) ) continue;

        apply_fwd_rule(ruleid, &state, &child);
        
        child_history = next_fwd_history(history, ruleid);

        const int cost = g_value + get_fwd_rule_cost(ruleid);

        if(heuristic->value(state) < INT32_MAX)
        {
            pair<bool, int> pair_value = f_bounded_visit(bound, cost, child, heuristic, child_history);

            if(pair_value.first) return pair_value;
            t = std::min(t, pair_value.second);
        }
    }

    return make_pair(false, t);
}

int ida_star(state_t state, Heuristic* heuristic)
{
    int bound = heuristic->value(state);

    while (true)
    {
        pair<bool, int> pair_value = f_bounded_visit(bound, 0, state, heuristic, init_history);

        if(pair_value.first) return pair_value.second;
        bound = pair_value.second;
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
    state_t state;
    ssize_t nchars;

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

        int goal = ida_star(state, heuristic);

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

