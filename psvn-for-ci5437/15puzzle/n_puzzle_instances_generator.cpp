#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std;

/* Manhattan distance for the heuristic of the n-puzzle */
int heuristic(int state[], int goal[], int max_size)
{
    int current_state[max_size];
    int goal_state[max_size];
    int mhd = 0;
    for( int i = 0; i < max_size; i++ ) {
        current_state[state[ i ]] = i;
        goal_state[goal[ i ]] = i;
    }

    int half_size = floor(sqrt(max_size));

    for( int i = 1; i < max_size; i++ ) {
        int first_half = abs((current_state[i] / half_size) - (goal_state[i] / half_size));
        int second_half = abs((current_state[i] % half_size) - (goal_state[i] % half_size));
        mhd += first_half + second_half;
    }

    return mhd;
}

/* Swaps to elements in the array with the index of first and second */
void swap(int array[], int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

/* Swaps the tile labeled with 1 and 2, this is to ensure the solvability of the instance */
void swap_for_solvability(int puzzle[], int size)
{
    int tile_1 = distance(puzzle, find(puzzle, puzzle + size, 1));
    int tile_2 = distance(puzzle, find(puzzle, puzzle + size, 2));
    swap(puzzle, tile_1, tile_2);
}

/* Generate two random numbers */
pair<int, int> get_random_pair(int size)
{
    int first = rand() % size;
    int second = rand() % size;

    while(second == first) second = rand() % size;

    return make_pair(first, second);
}

/* Calculate the number of inversions in the current state of the instance */
int get_inversions(int puzzle[], int size)
{
    int inv_count = 0;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (puzzle[j] && puzzle[i] && puzzle[i] > puzzle[j])
                inv_count++;
        }
    }
    return inv_count;
}

/* Find which row the blank is in */
int get_blank_position(int puzzle[], int size, int n)
{
    int pos = 1;

    for (int i = 0; i < size; i++)
    {
        if( puzzle[i] == 0 ) break;

        if(i % n == 0) pos++;    
    }

    return pos;
}

/* Checks if the instance is solvable, an instance is solvable if:
    1) If the width of the puzzle is odd then is solvable if the number of
        inversions is even
    2) If the width of the puzzle is even then is solvable if:
        a) The position of the blank is even and the number of inversions is odd 
        b) The position of the blank is odd and the number of inversions is even */
bool solvable(int puzzle[], int size)
{
    int inv_count = get_inversions(puzzle, size);
    int width = floor(sqrt(size));

    if( !(width & 1) )
    {
        int blank_position = get_blank_position(puzzle, size, width);
        if( blank_position & 1 )
            return !(inv_count & 1);
        else
            return inv_count & 1;
    }
    
    return !(inv_count & 1);
}

// void translate_instance(string instance_str, int instance[])
// { 
//     int j = 0;
  
//     for (int i = 0; instance_str[i] != '\0'; i++) {
//         if (instance_str[i] == ' '){
//             j++;
//             continue;
//         }
        
//         instance[j] = instance[j] * 10 + (instance_str[i] - 48);
//     }
// }

// string instance_to_string(int instance[], int size)
// {
//     string line;

//     for(int i = 0; i < size; i++)
//     {
//         if(instance[i] == 0)
//             line += "B";
//         else
//             line += to_string(instance[i]);
        
//         if(i != size - 1)
//             line += " ";
//     }

//     return line;
// }

int main(int argc, char *argv[])
{
    if ( (argc < 4) ) {
      cerr << "You must provide two integers on the command line." << endl;
      cerr << "First the threshold and second the size of the puzzle" << endl;
        exit(0);
    }
    
    int threshold = atoi(argv[1]);
    int size = atoi(argv[3]);
    size++;

    int h = 0;
    
    int state[size];
    int goal[size];

    for(int i = 0; i < size; i++)
    {
        state[i] = (i + 1) % size;
        goal[i] = (i + 1) % size;
    }

    // initialize random seed
    srand (time(NULL));
    
    // Loop until heuristic is bigger than the desire threshold
    while(h < threshold)
    {
        // Select two random tiles and swap them
        pair<int, int> tiles = get_random_pair(size);
        swap(state, tiles.first, tiles.second);

        // Select two random tiles again and swap again to ensure solvability
        tiles = get_random_pair(size);
        swap(state, tiles.first, tiles.second);

        // Calculate heuristic
        h = heuristic(state, goal, size);
    }

    if(!solvable(state, size)) swap_for_solvability(state, size);

    cout << "The state instance is" << endl;
    int len = sizeof(state) / sizeof(int);

    for (int i = 0; i < len; i++)
    {
        if(state[i] == 0)
            cout << "B";
        else
            cout << state[i];
        
        if(i != len - 1)
            cout << " ";
    }

    cout << endl;
    
    exit(0);
}
