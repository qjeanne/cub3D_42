#include "../cub3D.h"

int	ft_atoi(t_set *s, const char **str)
{
	long int	answer;

	answer = 0;
	if ((**str < '0' && **str > '9') || **str == '\0')
		error(s, "Invalid data");
	while (**str >= '0' && **str <= '9')
	{
		answer = (answer * 10) + (**str - '0');
		(*str)++;
	}
	if (**str != ',' && **str != '\t' && **str != ' ' && **str != '\0')
		error(s, "Invalid data");
	return (answer);
}
