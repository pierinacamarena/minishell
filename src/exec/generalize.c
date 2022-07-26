#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int	main(int ac, char **av)
{
	int	num_loops;
	int	end[2];
	int	i;

	i = 0;
	num_loops = atoi(av[1]);
	int	fd[num_loops][2];
	while (i < num_loops)
	{
		if (pipe(fd[i]) < 0)
			return 1;
	}

	i = 0;
	while (i < (num_loops - 1))
	
		pid_t pid;

		pid = fork();
		if (pid < 0)
			return 2;
		if (pid == 0)
		{
			int	j;

			j = 0;
			while (j < (num_loops - 1))
			{
				while (j < i)
				{
					close[j][0];
					close[j][1];
					j++;
				}
				if (j == i)
				{
					
				}
			}
			int x = 0;
			if (read(fd[i][0], &x, sizeof(int)) < 0)
				return 3;
			if (write(fd[i+1][1], &x, sizeof(int)) < 0)
				return 4;
			
		}
	}
}

void	exec()
{
	pid_t	pid;
	int		pipe[2];

	pid = fork()
	if (pid < 0)
		return 1;
	if (pid == 0)
	{

	}
}