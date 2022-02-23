#include "../cub3D.h"

static void	init_way(t_set *set)
{
	if (set->map[0] == 'N')
	{
		set_p(&set->me->plane, 0.66, 0);
		set_p(&set->me->dir, 0, -1);
	}
	else if (set->map[0] == 'W')
	{
		set_p(&set->me->plane, 0, -0.66);
		set_p(&set->me->dir, -1, 0);
	}
	else if (set->map[0] == 'S')
	{
		set_p(&set->me->plane, -0.66, 0);
		set_p(&set->me->dir, 0, 1);
	}
	else if (set->map[0] == 'E')
	{
		set_p(&set->me->plane, 0, 0.66);
		set_p(&set->me->dir, 1, 0);
	}
}

void	init_game(t_set *set)
{
	init_way(set);
	set->rotate = 0;
	set_p(&set->move, 0, 0);
	set->window = (t_window *)malloc(sizeof(t_window));
	set->window->image = (t_image *)malloc(sizeof(t_image));
	set_pos(&set->window->size, set->R[0], set->R[1]);
	init_window(set, set->window, set->window->image);
	init_image(set, set->window, set->window->image);
	xmp_files(set);
	update_draw(set);
}
