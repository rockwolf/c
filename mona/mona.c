/* See LICENSE file for license and copyright details. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//#include <string.h>
//#include <stdbool.h>
#include <ncurses.h>

char *current_time(char *fmt, char *buf);
char *afgets(char **, size_t *, FILE *);
static void taketail(FILE *, const char *, long);

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

void taketail(FILE *fp, const char *str, long n)
{
    char **ring;
    long i, j;
    size_t *size = NULL;
                
    if(!(ring = calloc(n, sizeof *ring)) || !(size = calloc(n, sizeof *size)))
        printf("calloc:");
    for(i = j = 0; afgets(&ring[i], &size[i], fp); i = j = (i+1)%n)
        ;
    if(ferror(fp))
        eprintf("%s: read error:", str);
                            
    do
    {
        if(ring[j])
        {
            fputs(ring[j], stdout);
            free(ring[j]);
        }
   } while((j = (j+1)%n) != i);
   free(ring);
   free(size);
}

void last_logs()
{
    if(!(fp = fopen("/var/log/messages.log", "r")))
        printf(Error, "fopen %s.", "/var/log/messages.log");
    read_file();
    fclose(fp);
}
