#include <stdio.h>
#include <stdlib.h>

#define  MAX_LEN     32

int main(int argc, char **argv)
{
    FILE *input;
    char *line = { '\0' };
    size_t len = 0;
    ssize_t read;

    input = fopen("input", "r");
    if (input == NULL)
        exit(1);

    int sum = 0, mass = 0, result = 0;
    while ((read = getline(&line, &len, input)) != -1) {
        mass = atoi(line);
        result = mass / 3 - 2;
        sum += result;
    }
        
    printf("Total Fuel Requirements: %d Units\n", sum); 

    return 0;
}
