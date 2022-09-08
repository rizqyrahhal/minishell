#include "../../Includes/minishell.h"

void	ex_exit(char **sp)
{
	if (sp[1] && sp[2] != NULL) {
		fprintf(stderr, "exit\nminishell: exit: too many arguments\n");
		r = 1;
		fprintf(stderr, "%d\n", r);
		exit (1);
	}
	else if (sp[1] && !is_str(sp[1])) {
		fprintf(stderr, "exit\nminishell: exit: %s: numeric argument required\n", sp[1]);
		r = 255;
		fprintf(stderr, "%d\n", r);
		exit (255);
	}
	fprintf(stderr, "exit\n");
	if (sp[1])
		r = ft_atoi(sp[1]) % 256;
	fprintf(stderr, "%d\n", r);
	exit(0);
}