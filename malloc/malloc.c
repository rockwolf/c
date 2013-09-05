#include <stdlib.h>
#include <stdio.h>

void func(int y)
{
    int a;
    char m;

    a = 0;
    m = 'c';
}

int main(int argc, char *argv[])
{
    int x;
    char c;

    char str[100];
    char *p_str = NULL;

    p_str = malloc(10000); 

    int x[10000];
    int *px;
    px = malloc(10000*4);

    strcpy(p_str, "Yeah!");

    func(x);

    return EXIT_SUCCESS;
}
