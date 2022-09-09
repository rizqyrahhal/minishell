#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s01;
	unsigned char	*s02;

	i = 0;
	s01 = (unsigned char *)s1;
	s02 = (unsigned char *)s2;
	while (s01[i] && s02[i] && s01[i] == s02[i])
		i++;
	if (s01[i] - s02[i] > 0)
		return (1);
	if (s01[i] - s02[i] < 0)
		return (-1);
	return (0);
}
