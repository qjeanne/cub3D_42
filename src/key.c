#include "../cub3D.h"

void	key_holder(t_set *s)
{
	if (s->move.y != 0)
		move_y(s, s->move.y);
	if (s->move.x != 0)
		move_x(s, s->move.x);
	if (s->rotate != 0)
		rotate(s, s->rotate);
	update_draw(s);
}

int	key_press(int key, t_set *s)
{
	if (key == W)
		s->move.y = -1;
	else if (key == D)
		s->move.x = 1;
	else if (key == SS)
		s->move.y = 1;
	else if (key == A)
		s->move.x = -1;
	else if (key == RIGHT)
		s->rotate = 1;
	else if (key == LEFT)
		s->rotate = -1;
	else if (key == ESC)
		error(s, NULL);
	key_holder(s);
	return (1);
}

int	key_release(int key, t_set *s)
{
	if (key == W || key == SS)
		s->move.y = 0;
	else if (key == D || key == A)
		s->move.x = 0;
	else if (key == RIGHT || key == LEFT)
		s->rotate = 0;
	return (1);
}

int	key_exit(t_set *s)
{
	error(s, NULL);
	return (1);
}
