/* See LICENSE file for license and copyright details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

extern char* argv0;

static void
usage(void)
{
    printf("usage: %s [timezone strings] [-d format] [+FORMAT]\n", "mona");//argv0);
    exit(1);
}

int main(int argc, char* argv[])
{
    double interval = 3.0;
    int i;
    // Time info
    char buf[BUFSIZ];
    char *fmt = "%Y-%m-%d %H:%M:%S %Z";
    struct tm *now = NULL;
    struct tm *(*tztime)(const time_t *) = localtime;
    const char *tz = "local";
    time_t t;
    //i /Time info

    if(argc == 0)
    {
        usage();
    }
    else if(argc > 0 && argv[0][0] == '+')
    {
        fmt = &argv[0][1];
    }
    t = time(NULL); 
    printf("Time\n");
    printf("-----------------------\n");
    t = time(NULL);
    if(!(now = tztime(&t)))
        printf("%stime failed\n", tz);

    strftime(buf, sizeof buf, fmt, now);
    puts(buf);

    /*for(i=0;i<10;i++)
    {
        sleep(interval);
        printf("test: %d\n", i);
    }
    */
    return EXIT_SUCCESS;
}
