#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int	num_loops;
	int	i;

	i = 0;
	num_loops = atoi(av[1]);
	while (i < num_loops)
	{

		i++;
	}
}