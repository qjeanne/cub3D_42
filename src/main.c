#include "../cub3D.h"

void	free_mp(char **mp)
{
	char	**copy;

	copy = mp;
	while (*mp[0] != '\0')
	{
		free(*mp);
		mp++;
	}
	free(copy);
}

void	error(t_set *set, char *str)
{
	if (str)
		printf("Error\n%s\n", str);
	clear_tex(set);
	free_path(set);
	free_sprite(set);
	if (set->map)
		free(set->map);
	if (set->mp)
		free_mp(set->mp);
	if (set->window)
		clear_window(set->window);
	if (set->me)
		free(set->me);
	exit(0);
}

t_set	*newset(void)
{
	t_set	*new;

	new = (t_set *)malloc(sizeof(t_set));
	new->NO = (t_tex *)malloc(sizeof(t_tex));
	new->SO = (t_tex *)malloc(sizeof(t_tex));
	new->WE = (t_tex *)malloc(sizeof(t_tex));
	new->EA = (t_tex *)malloc(sizeof(t_tex));
	new->NO->path = NULL;
	new->SO->path = NULL;
	new->WE->path = NULL;
	new->EA->path = NULL;
	new->s_path = NULL;
	new->sprite = NULL;
	new->F[0] = -1;
	new->C[0] = -1;
	new->map = (char *)malloc(sizeof(char));
	new->map[0] = '\0';
	new->mp = NULL;
	new->save = 0;
	new->rotate = 0;
	new->window = NULL;
	new->check = 0;
	return (new);
}

int	pathcheck(char *path)
{
	while (*path != '\0')
		path++;
	path -= 4;
	if (path[0] == '.' && path[1] == 'c' && path[2] == 'u' && path[3] == 'b')
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_set	*set;

	set = newset();
	if ((argc == 3 && !ft_strcmp(argv[2], "--save")) || argc > 3 || argc < 2
		|| pathcheck(argv[1]))
		error(set, "Wrong number of arguments or extension");
	if (argc == 3 && ft_strcmp(argv[2], "--save") && argv[2][6] == '\0')
		set->save = 1;
	else if (argc == 3 && ft_strcmp(argv[2], "--save") && argv[2][6] != '\0')
		error(set, "Wrong number of arguments or extension");
	parser(set, argv[1]);
	set->me = (t_me *)malloc(sizeof(t_me));
	check(set);
	set->check = 1;
	init_game(set);
	if (set->save == 1)
		save_bmp(set);
	else
	{
		mlx_hook(set->window->win, 2, 0, &key_press, set);
		mlx_hook(set->window->win, 3, 0, &key_release, set);
		mlx_hook(set->window->win, 17, 0, &key_exit, set);
		mlx_loop(set->window->ptr);
	}
	return (1);
}
