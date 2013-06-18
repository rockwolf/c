/* See LICENSE file for license and copyright details. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

char *current_time(char *fmt, char *buf);
unsigned int getlinenum(int n, char *str[]);
long unsigned int gettail(unsigned int linenum);

char            head1[] = {"\n------- "};
char            head2[] = {" -------\n"};
FILE *          fp;
int             filenum;
int             cc;
long int *      tail;

static void usage(void)
{
    printf("Usage:\n    %s -n=<n> [file1] [file2] [...]\n", "hina");//argv0);
    exit(EXIT_SUCCESS);
}

/*
 * Get the number of lines to display at the "tail" of each file from
 *  the command line.
 */
unsigned int getlinenum(int n, char *str[])
{
    unsigned int result;
    char parm_n[64]="";

    if(n == 0)
        return 0;
    //TODO: security problem: when param > 64: return 0 + print error
    sscanf(str[1], "-n=%63[^@]", parm_n);
    result = atoi(parm_n);
    return (unsigned int)result;
}

/*
 * Get pointers to position in file, for tail <n>
 * and return the total number of lines in the file.
 */
long unsigned int gettail(unsigned int linenum)
{
    unsigned int indx; //index = built-in function
    unsigned long int currline = 0L;
    tail = (long int *)malloc(sizeof(*tail) * linenum);
    if (!tail)
    {
        fputs("Insufficient memory.", stderr);
        exit(1);
    }
    tail[0] = ftell(fp);
    indx = 0;

    for (cc=getc(fp);cc!=EOF;cc=getc(fp))
    {
        if (cc == '\r')
        {
            currline++;
            cc = getc(fp);
            if (cc != '\n')
                ungetc(cc, fp);
            indx++;
            tail[indx] = ftell(fp);
        }
        else
        {
            if (cc == '\n')
            {
                currline++;
                cc = getc(fp);
                if (cc != '\r')
                    ungetc(cc, fp);
                indx++;
                tail[indx] = ftell(fp);
            }
        }
    }
    indx=currline - linenum;
    if (fseek(fp, tail[indx], 0) == -1)
    {
        fputs("\nFile seek error.", stderr);
        exit(1);
    }
    free(tail);
    return currline;
}

int main(int argc, char *argv[])
{
    char *fmt = "%Y-%m-%d %H:%M:%S %Z";
    char buf[BUFSIZ]; //BUFSIZ declared in <stdio.h>
    //FILE *fp;
    unsigned int linenum;
    
    /* option parsing */
    if(argc == 1)
    {
        usage();
    }
    else if(argc > 1)
    {
        if (argv[1][0] == '-')
        {
            if (argv[1][1] == 'n')
                linenum = getlinenum(argc, argv);
        }
    }

    for (filenum = 2; filenum < argc; ++filenum)
    {
        if (*argv[filenum] == '/')
            continue;
        fp = fopen(argv[filenum], "rb");
        if (!fp)
        {
            fputs(head1, stderr);
            fputs(" \"", stderr);
            fputs(argv[filenum], stderr);
            fputs("\" not found.", stderr);
            fputs(head2, stderr);
        }
        else
        {
            fputs(head1, stderr);
            fputs(" \"", stderr);
            fputs(argv[filenum], stderr);
            fputs("\" ", stderr);
            printf("%d", (int)gettail(linenum)); //gets tail + returns lines in file
            fputs(" lines", stderr);
            fputs(head2, stderr);
            for (cc = getc(fp); cc != EOF; cc = getc(fp))
            {
                fputc(cc, stdout);
            }
            fputs(head1, stderr);
            fputs(" \"", stderr);
            printf(current_time(fmt, buf));
            fputs("\" ", stderr);
            fputs(head2, stderr);
            fclose(fp);
        }
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
