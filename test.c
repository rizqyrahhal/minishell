//
// Created by Lahbib Semlali on 9/2/22.
//
#include <stdio.h>

int	main()
{
	int *fd[2];

	pipe(fd[0]);
	pipe(fd[1]);

	dup2(fd[0][1], 1);
	close(fd[0][0]);
	close(fd[0][1]);


	dup2(fd[0][0], 0);
	dup2(fd[1][1], 1);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[0][0]);
	close(fd[0][1]);


	dup2(fd[1][0], 0);

	close(fd[1][0])
	close(fd[1][1])


	int k = 2 - 1;
	int i = 0;



	dup2(fd[0][1], 1);
	close(fd[0][0]);
	close(fd[0][1]);

	while (i < k)
	{
		dup2(fd[i][0], 0);
		dup2(fd[i + 1][1], 1);
		close(fd[i + 1][0]);
		close(fd[i + 1][1]);
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}

	dup2(fd[1][0], 0);
	close(fd[1][0])
	close(fd[1][1])

}