/* See LICENSE file for license and copyright details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//#include <stdbool.h>
#include <ncurses.h>

char *current_time(char *fmt, char *buf);

static void usage(void)
{
    printf("usage: %s [timezone strings] [-d format] [+FORMAT]\n", "mona");//argv0);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    char *fmt = "%Y-%m-%d %H:%M:%S %Z";
    char buf[BUFSIZ]; //BUFSIZ declared in <stdio.h>
    
    /* option parsing */
    if(argc == 0)
    {
        usage();
    }
    else if(argc > 0 && argv[0][0] == '+')
    {
        fmt = &argv[0][1];
    }

    /* Init ncurses */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(0); //non-blocking getch()
    curs_set(0); //hide cursor

    /* time */
    do
    {
        clear();
        printw("\n");
        printw(current_time(fmt, buf));
        refresh();
    } while(getch() != 'q');
    endwin();
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
