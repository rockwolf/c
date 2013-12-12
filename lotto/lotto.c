#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_lim(int limit)
{
	/* return a random number between 0 and limit inclusive. */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do
    { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval+1;
}

int main(void)
{
	int i;
	
	srand(time(NULL));
	for(i = 0; i<6; i++)
	{
		int r = rand_lim(42);
		printf("%d ", r);
	}
	printf("\b");
	return EXIT_SUCCESS;
}
