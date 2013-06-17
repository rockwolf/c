/* See LICENSE file for license and copyright details. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
//#include <ncurses.h>

char *current_time(char *fmt, char *buf);
unsigned int getlinenum(int n, char *str[], size_t size);

char            head1[] = {"\n------- \""};
char            head2[] = {" -------\n"};
FILE *          fp;
int             filenum;
int             cc;
//unsigned int    linenum = 20;
unsigned int    indx; //index = built-in function
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
unsigned int getlinenum(int n, char *str[], size_t size)
{
    int i;
    char parm_n[20]="";

    if(n == 0)
        return 0;

    printf("test: size = %d", (int)size);
    for(i=3;i<(int)size;i++)
    {
       // start from 3: -n=543 => 5 = index 3 
       parm_n[i] = str[1][i];
    }
    printf("------>%s<--", parm_n);
    printf("test: %c", (char)(str[1][3]));
    printf("test: %d", (int)(str[1][3]));
    return (unsigned int)(str[1][3]); //ATTENTION: only works for 1 char this way. Need to get argv[1][3 till end]!
}

/*
**  Set the file pointer "fp" to "linenum - 1" lines before the end of
**  the file.
*/
void gettail(unsigned int linenum)
{
      char outstr[15];
      unsigned long int currline = 0L;

      tail = (long int *)malloc(sizeof(*tail) * linenum);
      if (!tail)
      {
            fputs("Insufficient memory.", stderr);
            exit(1);
      }
      tail[0] = ftell(fp);
      indx = 0;

      for (cc = getc(fp); cc != EOF; cc = getc(fp))
      {
            if (cc == '\r')
            {
                  ++currline;
                  cc = getc(fp);
                  if (cc != '\n')
                        ungetc(cc, fp);
                  ++indx;
                  indx %= linenum;
                  tail[indx] = ftell(fp);
            }
            else
            {
                  if (cc == '\n')
                  {
                        ++currline;
                        cc = getc(fp);
                        if (cc != '\r')
                              ungetc(cc, fp);
                        ++indx;
                        indx %= linenum;
                        tail[indx] = ftell(fp);
                  }
            }
      }
      fputs("\" ", stderr);
      snprintf(outstr, sizeof(currline), "%lu", currline);
      fputs(outstr, stderr);
      fputs(" lines", stderr);
      if (currline >= linenum - 1)
      {
            indx++;
            indx %= linenum;
      }
      else  indx = 0;

      if (fseek(fp, tail[indx], 0) == -1)
      {
            fputs("\nFile seek error.", stderr);
            exit(1);
      }
      free(tail);
}

int main(int argc, char *argv[])
{
    /*char *fmt = "%Y-%m-%d %H:%M:%S %Z";
    char buf[BUFSIZ]; //BUFSIZ declared in <stdio.h>
    */
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
                linenum = getlinenum(argc, argv, sizeof(argv)/sizeof(argv[1]));
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
            fputs(argv[filenum], stderr);
            fputs("\" not found.", stderr);
            fputs(head2, stderr);
        }
        else
        {
            fputs(head1, stderr);
            fputs(argv[filenum], stderr);
            gettail(linenum);
            fputs(head2, stderr);
            for (cc = getc(fp); cc != EOF; cc = getc(fp))
            {
                fputc(cc, stdout);
            }
            fclose(fp);
        }
    }
    /* time */
    /*do
    {
        system("cls")
        printf("\n");
        printf(current_time(fmt, buf));
    } while(getch() != 'q');
    */
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
