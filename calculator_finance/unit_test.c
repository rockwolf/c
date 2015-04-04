/* See LICENSE.txt for license and copyright information. */

#include <stdio.h>
#include "unit_test.h"
#include "calculator_finance.h"
#include "minunit.h"

int tests_run = 0;

static char* test_calculate_percentage_of()
{
    mu_assert(
            "[FAIL] Wrong result for calculate_percentage_of(2.0, 50.0)!",
            calculate_percentage_of(2.0, 50.0) == 4.0
    ); 
    return 0;
}

static char* test_all()
{
    mu_run_test(test_calculate_percentage_of);
    return 0;
}

int run_tests()
{

    puts(">>> Starting unit_tests...");
    char *result = test_all();
    if (result != 0)
        printf(">>> %s\n", result);
    else
        printf(">>> All tests succeeded.\n");
    printf(">>> Tests run: %d\n", tests_run);
    return 0;
}
