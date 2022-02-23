#include "../cub3D.h"

int	checkparam(t_set *set)
{
	int	answer;
	int	x;
	int	y;

	answer = 1;
	if (set->R[0] < 1 || set->R[1] < 1)
		answer = 0;
	else if (set->F[0] < 0 || set->F[1] < 0 || set->F[2] < 0 || set->C[0] < 0
		|| set->C[1] < 0 || set->C[2] < 0 || set->F[0] > 255 || set->F[1] > 255
		|| set->F[2] > 255 || set->C[0] > 255 || set->C[1] > 255
		|| set->C[2] > 255)
		answer = 0;
	else if (set->NO->path == NULL || set->SO->path == NULL
		|| set->WE->path == NULL || set->EA->path == NULL
		|| set->s_path == NULL)
		answer = 0;
	mlx_get_screen_size(&x, &y);
	if (set->R[0] > x)
		set->R[0] = x;
	if (set->R[1] > y)
		set->R[1] = y;
	if (set->F[0] == -1 || set->C[0] == -1)
		return (0);
	color(set);
	return (answer);
}

void	reline(t_set *set, char *str)
{
	set->map = ft_strjoin(set->map, str);
	set->map = ft_strjoin(set->map, "\n");
}

static void	step_map(t_set *set, int *i, int j)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = set->map[*i];
	str[1] = '\0';
	set->mp[j] = ft_strjoin(set->mp[j], str);
	*i += 1;
	free(str);
}

void	makemap(t_set *set)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (set->map[i] != '\0')
		if (set->map[i++] == '\n')
			j++;
	set->mp = (char **)malloc(sizeof(char *) * (j + 1));
	i = 0;
	j = 0;
	while (set->map[i] != '\0')
	{
		set->mp[j] = (char *)malloc(sizeof(char));
		set->mp[j][0] = '\0';
		while (set->map[i] != '\n')
			step_map(set, &i, j);
		j++;
		i++;
	}
	set->mp[j] = (char *)malloc(sizeof(char) * 1);
	set->mp[j][0] = '\0';
	free(set->map);
	set->map = NULL;
}

void	getmap(int *fd, char *str, t_set *set)
{
	if (checkparam(set) == 0)
		error(set, "Invalid data");
	reline(set, str);
	while (get_next_line(*fd, &str))
	{
		if (*str == '\0')
			error(set, "Invalid data");
		reline(set, str);
		free(str);
	}
	reline(set, str);
	free(str);
	*fd = 0;
	makemap(set);
}
