#include "../cub3D.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	answer;

	answer = 1;
	while (*s2 != '\0' && *s1 != '\0')
		if (*s2++ != *s1++)
			answer = 0;
	return (answer);
}
