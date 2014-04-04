/* See LICENSE file for license and copyright details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

char *current_time(char *fmt, char *buf);
bool unit_test();

static void usage(void)
{
    printf("Usage:\n    %s\n", "hina");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    /* Version info */
    puts("Hina version 0.1");
    puts("Press Ctrl+c to quit\n");
    
    if (argc > 1 && argv)
    {
        usage();
    }

    /* Main loop */
    while (1)
    {
        char* input = readline("hina> ");
        add_history(input);
        printf("Entered %s\n", input);
        free(input);
    }
  return EXIT_SUCCESS;
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
