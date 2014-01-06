/* See LICENSE.txt file for license info. */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    argc = argc;
    argv = argv;
    
    char *password = getpass("Password: ");

    printf("The password is: %s\n", password);

    return 1;
}
