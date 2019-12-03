#include <stdio.h>
#include <stdlib.h>

#define  MAX_LEN     32

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "error: invalid parameters (not enough arguments)\n", MAX_LEN);
        fprintf(stderr, "usage: ./rocket (mass)\n", MAX_LEN);
        exit(1);
    }

    // convert the CLI argument from a string to an integer
    int mass = atoi(argv[1]);
    // store the result of the puzzle's basic formula in `result`
    int result = mass / 3 - 2;
    printf("Fuel Requirements: %d Units\n", result); 

    return 0;
}
