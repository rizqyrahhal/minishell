#include "../../includes/execution.h"

char**	re_alloc(char **s, int k)
{
	int		i;
	int		j;
	char	**sp;

	i = 0;
	j = 0;
	sp = malloc(arr_size(s) * sizeof (char *));
	while (s[i] && j < (arr_size(s) - 1))
	{
		if (i != k){
			sp[j] = ft_strdup(s[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	sp[j] = 0;
	return (sp);
}

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

	k = 0;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-') {
		if (is_accept(cmd[i])) {
			k++;
			cmd = re_alloc(cmd, i);
		}
		else
			break;
	}
	i = 1;
	while (cmd[i])
	{
		printf("%s ", cmd[i]);
		i++;
	}
	if (k == 0)
		printf("\n");
	myenv->status = 0;
}