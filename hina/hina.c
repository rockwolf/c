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
#define DATA_FILE "hina.dat"
#define VERSION_INFO "Hina version 0.1"
#define CHUNK 1024
#define BUF 4


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
    printf("    %s: show bookmarked commands.\n", CMD_CMD);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    //char buf[CHUNK];
    size_t nread;
    int i;

    if (argc > 1 && argv)
    {
        usage();
    }

    /* Read database */
    char *buf = malloc(CHUNK);

    if (buf == NULL)
    {
        puts("Error allocating memory while reading database.");
        return EXIT_FAILURE;
    }
    
    /* test string_split */
    char months[50];
    char *s[BUF];
    //char test[50];

    strncpy(months, "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC", 50);
    //char *tokens[50];
    printf("months=[%s]\n\n", months);

    string_split(months, ",", s, BUF);
    if (s)
    {
        for (i = 0; i< (BUF+1); i++)
        {
            //if(s[i] )
                printf("s[%d] = %s\n", i, s[i]);
        }
    }

    /* /test string_split */

    fp = fopen(DATA_FILE, "r");
    if (fp)
    {
        while ((nread = fread(buf, 1, CHUNK, fp)) > 0)
        {
            // TODO: write to char splitstr[BUF] instead of stdout.
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
        char *input = readline("hina> ");
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

char** str_split(char* a_str, const char a_delim)
{
    char** result = 0;
    size_t count = 0;
    char* tmp = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    
    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);
    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;
    result = malloc(sizeof(char*) * count);
    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}

void string_split(char *a_string, const char *a_delimiter, char *split_strings[], size_t split_size)
{
    char *p = NULL;
    int n_delims = 0;

    p = strtok(a_string, a_delimiter);

    printf("test: %d\n", (int)split_size);
    /* Split string and append tokens to the result */
    while ((p != NULL)) // && (n_delims <= (int)split_size))
    {
        //result = realloc(result,  ++n_delims * sizeof(char) * BUF);

        /*if (split_strings == NULL)
        {
            exit(EXIT_FAILURE); //memory allocation failed
        }*/

        split_strings[n_delims - 1] = *p;

        p = strtok(NULL, a_delimiter);
    }

    /* Add space for trailing NULL. */
    //result = realloc(result, sizeof (char *) * (n_delims + 1));
    split_strings[n_delims] = 0;
}

bool unit_test()
{
    bool passed = true;

    if(passed)
        printf("All tests passed.\n");
    return passed;
}
