#include "../cub3D.h"

void	move_y(t_set *s, int way)
{
	t_p		copy_pos;
	double	n;

	set_p(&copy_pos, s->me->pos.x, s->me->pos.y);
	n = -way * s->me->dir.x * SPEED;
	copy_pos.x += n;
	if (s->mp[(int)copy_pos.y][(int)copy_pos.x] == '0')
		set_p(&s->me->pos, copy_pos.x, copy_pos.y);
	n = -way * s->me->dir.y * SPEED;
	copy_pos.y += n;
	if (s->mp[(int)copy_pos.y][(int)copy_pos.x] == '0')
		set_p(&s->me->pos, copy_pos.x, copy_pos.y);
}

void	move_x(t_set *s, int way)
{
	t_p		copy_pos;
	double	n;

	set_p(&copy_pos, s->me->pos.x, s->me->pos.y);
	n = -way * s->me->dir.y * SPEED;
	copy_pos.x += n;
	if (s->mp[(int)copy_pos.y][(int)copy_pos.x] == '0')
		set_p(&s->me->pos, copy_pos.x, copy_pos.y);
	n = way * s->me->dir.x * SPEED;
	copy_pos.y += n;
	if (s->mp[(int)copy_pos.y][(int)copy_pos.x] == '0')
		set_p(&s->me->pos, copy_pos.x, copy_pos.y);
}

void	rotate(t_set *s, int way)
{
	double	dir_x;
	double	plane_x;

	dir_x = s->me->dir.x;
	plane_x = s->me->plane.x;
	s->me->dir.x = s->me->dir.x * cos(way * TURN) - s->me->dir.y
		* sin(way * TURN);
	s->me->dir.y = dir_x * sin(way * TURN) + s->me->dir.y * cos(way * TURN);
	s->me->plane.x = s->me->plane.x * cos(way * TURN) - s->me->plane.y
		* sin(way * TURN);
	s->me->plane.y = plane_x * sin(way * TURN) + s->me->plane.y
		* cos(way * TURN);
}
