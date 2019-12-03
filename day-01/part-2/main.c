#include <stdio.h>
#include <stdlib.h>

int get_fuel_requirement(int mass)
{
    return mass / 3 - 2;
}

int get_compound_fuel(int mass)
{
    int result = get_fuel_requirement(mass);
    if (get_fuel_requirement(result) > 0) {
        return get_fuel_requirement(mass) + get_compound_fuel(get_fuel_requirement(mass));
    }
    return result;
}

int main(void)
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
        result = get_compound_fuel(mass);
        sum += result;
    }
        
    printf("Total Fuel Requirements: %d Units\n", sum); 

    return 0;
}

