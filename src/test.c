#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
    char arr[100];
    printf("%s\n", getcwd(arr, 100));
    chdir("..");
    printf("%s\n", getcwd(arr, 100));
    chdir("..");
    printf("%s\n", getcwd(arr, 100));
    return (0);
}