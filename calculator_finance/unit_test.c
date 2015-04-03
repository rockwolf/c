/* See LICENSE.txt for license and copyright information. */

#include <stdio.h>

int test_calculate_percentage_of();

int test_calculate_percentage_of()
{
    double result;
    result = calculate_percentage_of(2.0, 50.0); 
    printf("calculate_percentage_of(2.0, 50.0) = %.2f [%s]\n", result, bool_to_success(result == 4.0));
}
