/* See LICENSE file for license and copyright details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

char *current_time(char *fmt, char *buf);
bool unit_test();

static void usage(void)
{
    printf("Usage:\n    %s\n", "hina");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
}

char *current_time(char *fmt, char *buf)
{
    struct tm *now = NULL;
    struct tm *(*tztime)(const time_t *) = localtime;
    const char *tz = "local";
    time_t t;
    
    t = time(NULL);
    if(!(now = tztime(&t)))
        printf("%stime failed\n", tz);
    strftime(buf, BUFSIZ, fmt, now);
    return buf;
}

bool unit_test()
{
    bool passed = true;

    if(passed)
        printf("All tests passed.\n");
    return passed;
}
