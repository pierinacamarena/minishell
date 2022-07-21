#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	printf("%s\n", getcwd(NULL, 0));
	chdir("..");
	printf("%s\n", getcwd(NULL, 0));
	if (chdir("microshell") == -1)
		printf("directory does not exist\n");
	// extern char	**environ;
	// // char		*var[3] = {"PATH=||path||", "HOME=||home||", NULL};

	// // environ = var;
	// printf("%s\n", getenv("PATH"));
	// printf("%s\n", getenv("HOME"));
	// printf("%s\n", getenv("OLDPWD"));
	// printf("%s\n", getenv("PWD"));
    // chdir("..");
	// printf("%s\n", getenv("PATH"));
	// printf("%s\n", getenv("HOME"));
	// printf("%s\n", getenv("OLDPWD"));
	// printf("%s\n", getenv("PWD"));
	return (0);
}