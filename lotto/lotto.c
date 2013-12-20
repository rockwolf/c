/* See LICENSE.txt file for license info. */

#define NUM             6
#define RAND_LIMIT     42

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_lim(int limit);

/* return a random number between 0 and limit inclusive. */
int rand_lim(int limit)
{
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do
    { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval+1;
}

int main(int argc, char *argv[])
{
	int i;
	
	srand(time(NULL));
	for(i = 0; i<NUM; i++)
	{
		int r = rand_lim(RAND_LIMIT);
		printf("%d ", r);
	}
	printf("\b");
	return EXIT_SUCCESS;
}
