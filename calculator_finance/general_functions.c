/* See LICENSE.txt file for license and copyright information. */

#include "general_functions.h"

char* bool_to_success(_Bool a_bool)
{
    return a_bool ? "success" : "failure";
}

char* bool_to_string(_Bool a_bool)
{
    return a_bool ? "true" : "false";
}
