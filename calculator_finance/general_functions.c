/* See LICENSE.txt file for license and copyright information. */

#include <math.h>
#include "general_functions.h"

char* bool_to_success(_Bool a_bool)
{
    return a_bool ? "success" : "failure";
}

char* bool_to_string(_Bool a_bool)
{
    return a_bool ? "true" : "false";
}

int equals(double d1, double d2, double precision)
{
    double eps1 = fabs(d1), eps2 = fabs(d2), eps;
    eps = (eps1 > eps2) ? eps1 : eps2;
    if (eps == 0.0)
        return 0;
    eps *= precision;
    return (fabs(d1 - d2) < eps);
}
