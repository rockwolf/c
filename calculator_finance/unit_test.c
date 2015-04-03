/* See LICENSE.txt for license and copyright information. */

#include <stdio.h>
#include "calculator_finance.h"
#include "general_functions.h"

int test_calculate_percentage_of()
{
    double l_result;
    int l_ok, l_testcount, l_failed, l_succeeded;

    l_testcount = 0;
    l_failed = 0;
    l_succeeded = 0;

    puts("Starting unit_tests...\n");
    puts("Results\n");
    puts("-------\n");
    l_testcount++;
    printf(">>> Test %d\n", l_testcount);
    l_result = calculate_percentage_of(2.0, 50.0); 
    l_ok = (l_result == 4.0);
    if (l_ok)
        l_succeeded++;
    else
        l_failed++;
    printf(
            "calculate_percentage_of(2.0, 50.0) = %.2f [%s]\n",
            l_result,
            bool_to_success(l_ok)
    );
    puts("\nSummary");
    puts("---------");
    printf("total: %d\nfailed: %d\nsucceeded: %d\n",
            l_testcount,
            l_failed,
            l_succeeded
    );

    return 0;
}
