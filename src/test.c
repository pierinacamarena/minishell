#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	extern char	**environ;
	// char		*var[3] = {"PATH=||path||", "HOME=||home||", NULL};

	// environ = var;
	printf("%s\n", getenv("PATH"));
	printf("%s\n", getenv("HOME"));
	printf("%s\n", getenv("OLDPWD"));
	printf("%s\n", getenv("PWD"));
    chdir("..");
	printf("%s\n", getenv("PATH"));
	printf("%s\n", getenv("HOME"));
	printf("%s\n", getenv("OLDPWD"));
	printf("%s\n", getenv("PWD"));
	return (0);
}