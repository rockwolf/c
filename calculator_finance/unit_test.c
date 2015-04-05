/* See LICENSE.txt for license and copyright information. */

#include <stdio.h>
#include "unit_test.h"
#include "unit_test_trade.h"
#include "minunit.h"

int tests_run = 0;

int run_tests()
{

    puts(">>> Starting unit_tests for trading...");
    char *result = test_all_trade();
    if (result != 0)
        printf(">>> %s\n", result);
    else
        printf(">>> All tests succeeded.\n");
    printf(">>> Tests run: %d\n", tests_run);
    return 0;
}
