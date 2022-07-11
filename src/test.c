#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
    char *envp;

    envp = getcwd(NULL, 0);
    printf("%s\n", envp);
    chdir("..");
    envp = getcwd(NULL, 0);
    printf("%s\n", envp);
    chdir("..");
    envp = getcwd(NULL, 0);
    printf("%s\n", envp);
    chdir("..");
    envp = getcwd(NULL, 0);
    printf("%s\n", envp);
    chdir("github/minishell/src");
    envp = getcwd(NULL, 0);
    printf("%s\n", envp);
    // char arr[100];
    // printf("%s\n", getcwd(arr, 100));
    // chdir("..");
    // printf("%s\n", getcwd(arr, 100));
    // chdir("..");
    // printf("%s\n", getcwd(arr, 100));
    return (0);
}