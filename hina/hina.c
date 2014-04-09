/* See LICENSE file for license and copyright details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <assert.h>

#include "hina.h"

#define CMD_QUIT "quit"
#define CMD_HELP "help"
#define CMD_LIST "list"
#define CMD_LS "ls"
#define CMD_BM "bm"
#define CMD_CMD "cmd"
#define CMD_REPORT "report"
#define DATA_FILE "hina.dat"
#define VERSION_INFO "Hina version 0.1"
#define CHUNK 1024


static void usage(void)
{
    printf("Usage:\n    %s\n", "hina");
    exit(EXIT_SUCCESS);
}

static void help(void)
{
    printf("Available commands:\n");
    printf("    %s: quit.\n", CMD_QUIT);
    printf("    %s: shows this help.\n", CMD_HELP);
    printf("    %s|%s: list everything.\n", CMD_LIST, CMD_LS);
    printf("    %s: show bookmarked urls.\n", CMD_BM);
    printf("    %s: show bookmarked reports.\n", CMD_REPORT);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    //char buf[CHUNK];
    size_t nread;

    if (argc > 1 && argv)
    {
        usage();
    }

    /* test string_split */
    char months[50];
    //char test[50];

    strcpy(months, "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC");
    //char *tokens[50];
    printf("months=[%s]\n\n", months);

    string_split(months, ",");
    /* /test string_split */

    /* Read database */
    char *buf = malloc(CHUNK);

    if (buf == NULL)
    {
        puts("Error allocating memory while reading database.");
        return EXIT_FAILURE;
    }
    
    fp = fopen(DATA_FILE, "r");
    if (fp)
    {
        while ((nread = fread(buf, 1, CHUNK, fp)) > 0)
        {
            fwrite(buf, 1, nread, stdout);
            if (ferror(fp))
            {
                printf("Error reading chunk in %s.", DATA_FILE);
            }
        } 
        fclose(fp);
    }
    else
    {
        printf("Error reading %s.", DATA_FILE);
    }

    puts(VERSION_INFO);
    puts("Enter 'quit' to quit.\n");

    /* Main loop */
    while (1)
    {
        char* input = readline("hina> ");
        add_history(input);
        if(strncmp(input, CMD_QUIT, strlen(CMD_QUIT)) == 0)
        {
            free(input);
            break;
        }
        else if(strncmp(input, CMD_HELP, strlen(CMD_HELP)) == 0)
        {
            help();
        }
        else if(strncmp(input, CMD_BM, strlen(CMD_BM)) == 0)
        {
           puts("Need to show some bookmarks."); 
        }
        else if(strncmp(input, CMD_CMD, strlen(CMD_CMD)) == 0)
        {
           puts("Need to show some commands."); 
        }
        else if
        (
            strncmp(input, CMD_LIST, strlen(CMD_LIST)) == 0
            || strncmp(input, CMD_LS, strlen(CMD_LS)) == 0
        )
        {
            puts("Need to show everything here.");
        }
        else if(strncmp(input, CMD_REPORT, strlen(CMD_REPORT)) == 0)
        {
            puts("Need to show some reports.");
        }
        else
            puts("Unknown command...");
        free(input);
    }
  return EXIT_SUCCESS;
}

/*char *current_time(char *fmt, char *buf)
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
}*/

void string_split(char *a_string, const char *a_delimiter)
{
    char *result = NULL;
    char *p = NULL;
    int n_delims = 0;
    int i;

    printf("\ntest: a_string=%s", a_string);
    p = strtok(a_string, a_delimiter);


    /* Split string and append tokens to the result */
    while (p != NULL)
    {
        //result = realloc(result, sizeof(char *) * ++n_delims);
        printf("test1a: %s\n", p);

        /*if (result == NULL)
        {
            puts("dang");
            exit(EXIT_FAILURE); //memory allocation failed
        }*/

        //result[n_delims - 1] = *p;
        printf("test1b: delim = %s", a_delimiter);

        puts("test1c");
        p = strtok(NULL, a_delimiter);
    }
    puts("test4");

    /* Add space for trailing NULL. */
    result = realloc(result, sizeof (char *) * (n_delims + 1));
    result[n_delims] = 0;

    if (result)
    {
        for (i = 0; i< (n_delims + 1); i++)
            printf("result[%d] = %c\n", i, result[i]);
    }
    //return result;
}

bool unit_test()
{
    bool passed = true;

    if(passed)
        printf("All tests passed.\n");
    return passed;
}
