#include "../cub3D.h"

char	*skip_dot(t_set *set, char *line)
{
	line = skip(line);
	if (*line++ != ',')
		error(set, "Invalid data");
	line = skip(line);
	return (line);
}

void	get_textures_take(t_set *set, char *copy, char *str, int size)
{
	if (copy[0] == 'N')
		set->NO->path = str - size;
	else if (copy[0] == 'W')
		set->WE->path = str - size;
	else if (copy[0] == 'E')
		set->EA->path = str - size;
	else if (copy[0] == 'S' && copy[1] == 'O')
		set->SO->path = str - size;
	else
		set->s_path = str - size;
}

void	getF_take(t_set *set, int a, int b, int c)
{
	if (set->F[0] == -1)
	{
		set->F[0] = a;
		set->F[1] = b;
		set->F[2] = c;
	}
	else
		error(set, "Invalid data");
}

void	getC_take(t_set *set, int a, int b, int c)
{
	if (set->C[0] == -1)
	{
		set->C[0] = a;
		set->C[1] = b;
		set->C[2] = c;
	}
	else
		error(set, "Invalid data");
}

int	parser_util(t_set *set, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error(set, "Invalid file");
	return (fd);
}
