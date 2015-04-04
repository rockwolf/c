/* See LICENSE.txt file for license and copyright information. */

#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
    if (argc > 1)
        printf("No parameters required... [%s]\n", argv[1]);

    run_tests();
    return 0;
}
