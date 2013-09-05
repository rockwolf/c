#include <stdlib.h>
#include <stdio.h>

struct rectangle
{
    int length;
    int width;
};

int area(struct rectangle *rect)
{
    return rect->length * rect->width;
}

int main(int argc, char *argv[])
{
    struct rectangle rect1;
    int rect1_area;

    rect1.length = 10;
    rect1.width = 5;
   
    rect1_area = area(&rect1); 

    printf("Area of rect1 is %d.\n", rect1_area);
    
    return EXIT_SUCCESS;
}
