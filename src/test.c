#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
    // pid_t child;
    // pid_t child_2;

    // child = fork();
    // if (child != 0)
    //     child_2 = fork();

        
    printf("%s\n", getenv("ENV"));
    return (0);
}