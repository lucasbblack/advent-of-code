#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int perform(int *arr, int i)
{
    // get the op code and check for end of program
    // to ensure we don't index out of range
    int op = arr[i];
    if (op == 99)
       return 1;

    // position of the first input
    int a = arr[i + 1];
    // position of the second input
    int b = arr[i + 2];
    // location to store the result in the array
    int c = arr[i + 3];

    // addition operation
    if (op == 1) {
        arr[c] = arr[a] + arr[b];
    } else if (op == 2) {
        arr[c] = arr[a] * arr[b];
    }

    return 0;
}

void reset_state(int *curr, int orig[])
{
    // clear memory
    for (int i = 0; i < 149; i++) {
        curr[i] = orig[i];
    }
}


int main(void)
{
    // static data
    int original_state[] = { 
                    1,0,0,3,
                    1,1,2,3,
                    1,3,4,3,
                    1,5,0,3,
                    2,6,1,19,
                    1,19,5,23,
                    2,9,23,27,
                    1,5,27,31,
                    1,5,31,35,
                    1,35,13,39,
                    1,39,9,43,
                    1,5,43,47,
                    1,47,6,51,
                    1,51,13,55,
                    1,55,9,59,
                    1,59,13,63,
                    2,63,13,67,
                    1,67,10,71,
                    1,71,6,75,
                    2,10,75,79,
                    2,10,79,83,
                    1,5,83,87,
                    2,6,87,91,
                    1,91,6,95,
                    1,95,13,99,
                    2,99,13,103,
                    1,103,9,107,
                    1,10,107,111,
                    2,111,13,115,
                    1,10,115,119,
                    1,10,119,123,
                    2,13,123,127,
                    2,6,127,131,
                    1,13,131,135,
                    1,135,2,139,
                    1,139,6,0,
                    99,2,0,14,0 };
    // allocate array
    int *current_state = calloc(149, sizeof(int));

    // loop each possible pair within the range
    int set_breakpoint = 0;
    for (int noun = 0; noun < 100; noun++) {
        // break out of nested loops
        if (set_breakpoint)
            break;

        for (int verb = 0; verb < 100; verb++) {
            reset_state(current_state, original_state);

            // try every pair of A and B (A, B inclusive 0 - 99)
            current_state[1] = noun;
            current_state[2] = verb;

            // perform the program with initialize program parameters
            for (int j = 0; j < 149; j += 4) {
                int n = perform(current_state, j);
                if (n)
                    break;
            }

            // search for the pair with the desiginated output (19690720)
            if (current_state[0] == 19690720) {
                printf("Noun: %2d  Verb: %2d  Output: %d\n", noun, verb, current_state[0]);
                printf("100 * %2d + %2d = %d\n", noun, verb, 100 * noun + verb);

                set_breakpoint = 1;
                break;
            }
        }
    }
        
    // free dynamic memory
    free(current_state);
    return 0;
}

