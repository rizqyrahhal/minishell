#include "../../includes/execution.h"

int	is_accept(char *s)
{
	int i;

	i = 1;
	if (s[1] == '\0')
		return  (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ex_echo(char **cmd, t_envp *myenv)
{
	int i;
	int k;

	k = 1;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-') {
		if (is_accept(cmd[i])) {
			k++;
			i++;
		}
		else
			break;
	}
	i = k;
	while (cmd[i])
	{
		printf("%s ", cmd[i]);
		i++;
	}
	if (k == 1)
		printf("\n");
	myenv->status = 0;
}