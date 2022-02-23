#include "../cub3D.h"

char	*skip(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

void	getR(t_set *set, char *line)
{
	line++;
	line = skip(line);
	if (*line < '0' || *line > '9')
		error(set, "Invalid data");
	set->R[0] = ft_atoi(set, (const char **)&line);
	line = skip(line);
	if (*line < '0' || *line > '9')
		error(set, "Invalid data");
	set->R[1] = ft_atoi(set, (const char **)&line);
}

void	get_textures(t_set *set, char *line)
{
	int		size;
	char	*str;
	char	*copy;

	copy = line;
	size = 0;
	if (line[0] == 'S' && line[1] == ' ')
		line++;
	else
		line += 2;
	if (*line != ' ')
		error(set, "Invalid data");
	line = skip(line);
	while (line[size] != '\0')
		size++;
	str = (char *)malloc(sizeof(char) * size);
	while (*line != '\0')
		*str++ = *line++;
	*str = '\0';
	get_textures_take(set, copy, str, size);
}

void	getFC(t_set *set, char *line, char first)
{
	int		a;
	int		b;
	int		c;

	line++;
	line = skip(line);
	a = ft_atoi(set, (const char **)&line);
	line = skip_dot(set, line);
	b = ft_atoi(set, (const char **)&line);
	line = skip_dot(set, line);
	c = ft_atoi(set, (const char **)&line);
	line = skip(line);
	if (*line != '\0')
		error(set, "Invalid data");
	if (first == 'F')
		getF_take(set, a, b, c);
	else
		getC_take(set, a, b, c);
}

void	parser(t_set *set, char *path)
{
	int		fd;
	char	*l;
	char	*copy;

	fd = parser_util(set, path);
	while (fd > 0 && get_next_line(fd, &l))
	{
		copy = l;
		if (*l != '\0')
		{
			l = skip(l);
			if (*l == 'R')
				getR(set, l);
			else if ((l[0] == 'N' && l[1] == 'O')
				|| (l[0] == 'S' && l[1] == ' ') || (l[0] == 'W' && l[1] == 'E')
				|| (l[0] == 'E' && l[1] == 'A') || (l[0] == 'S' && l[1] == 'O'))
				get_textures(set, l);
			else if (l[0] == 'F' || l[0] == 'C')
				getFC(set, l, l[0]);
			else
				getmap(&fd, copy, set);
		}
		free(copy);
	}
}
