/* See LICENSE.txt file for license info. */

#define NUM             6
#define RAND_LIMIT     42

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_lim(int limit);
int number_is_taken(int n, int n_array[]);
void print_numbers(int numbers[]);

int main(int argc, char *argv[])
{
    int i;
    int numbers[NUM] = {0};

    if (argc > 1)
    {
        printf("No parameters required, [%s...] given.\n", argv[1]);
        exit(1);
    }
    
    srand(time(NULL)); //randomize the seed
    for(i = 0; i < NUM;)
    {
        int r = rand_lim(RAND_LIMIT);
        if(number_is_taken(r, numbers) == 0)
        {
            numbers[i] = r;
            i++;
        }
    }
    print_numbers(numbers);
    
    return EXIT_SUCCESS;
}

/* Returns a random number between 0 and limit inclusive. */
int rand_lim(int limit)
{
    int divisor = RAND_MAX/(limit+1);
    int result;

    do
    { 
        result = rand() / divisor;
    } while (result > limit);
    
    return result;
}

/* Checks if the chosen int is in the given int array. */
int number_is_taken(int n, int n_array[])
{
    int i, result;
    
    for (i = 0; i < NUM; i++)
    {
    	result = (n_array[i] == n) ? 1 : 0;
    	if(result == 1)
            break;
    }
    
    return result;
}

/* Prints the numbers. */
void print_numbers(int numbers[])
{
    int i;
    
    for(i = 0; i < NUM; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\b\n");
}
