#include "../cub3D.h"

void	color(t_set *set)
{
	set->F[0] = set->F[0] << 16 | set->F[1] << 8 | set->F[2];
	set->C[0] = set->C[0] << 16 | set->C[1] << 8 | set->C[2];
}

static void	check_wall(t_set *s, int i, int j)
{
	if (s->mp[i][j] == 'N' || s->mp[i][j] == 'S' || s->mp[i][j] == 'E'
	|| s->mp[i][j] == 'W' || s->mp[i][j] == '0' || s->mp[i][j] == '2')
	{
		if (s->mp[i + 1][j] && s->mp[i - 1][j] && s->mp[i][j + 1]
			&& s->mp[i][j - 1])
		{
			if (s->mp[i + 1][j] == ' ' || s->mp[i - 1][j] == ' '
			|| s->mp[i][j + 1] == ' ' || s->mp[i][j - 1] == ' ')
				error(s, "Invalid map");
		}
		else
			error(s, "Invalid map");
	}
	else if (s->mp[i][j] != '1' && s->mp[i][j] != ' ')
		error(s, "Invalid map");
}

static void	player(t_set *set, int i, int j)
{
	if (set->mp[i][j] == 'N' || set->mp[i][j] == 'S' || set->mp[i][j] == 'E'
	|| set->mp[i][j] == 'W')
	{
		if (set->map[0] == '\0')
		{
			set->map[0] = set->mp[i][j];
			set_p(&set->me->pos, (double)j + 0.5, (double)i + 0.5);
			set->mp[i][j] = '0';
		}
		else
			error(set, "Invalid map");
	}
	else if (set->mp[i][j] == '2')
		new_sprite(set, j, i);
}

void	check(t_set *set)
{
	int	i;
	int	j;

	if (set->mp == NULL)
		error(set, "Invalid file");
	i = 0;
	j = 0;
	set->map = (char *)malloc(sizeof(char));
	set->map[0] = '\0';
	set->map[1] = '\0';
	while (set->mp[i][0] != '\0')
	{
		while (set->mp[i][j] != '\0')
		{
			player(set, i, j);
			check_wall(set, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	if (set->map[0] == '\0')
		error(set, "Invalid data");
}
