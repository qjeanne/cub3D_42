#include "../cub3D.h"

static void	ray_position(t_set *set, t_me *s, int x)
{
	s->cameraX = 2 * x / (double)set->R[0] - 1;
	s->rayDir.x = s->dir.x + s->plane.x * s->cameraX;
	s->rayDir.y = s->dir.y + s->plane.y * s->cameraX;
	if (s->rayDir.x == 0 && s->rayDir.y == 0)
	{
		s->deltaDist.x = 0;
		s->deltaDist.y = 0;
	}
	else if (s->rayDir.x == 0)
	{
		s->deltaDist.y = 0;
		s->deltaDist.x = 1;
	}
	else if (s->rayDir.y == 0)
	{
		s->deltaDist.x = 0;
		s->deltaDist.y = 1;
	}
	else
	{
		s->deltaDist.x = fabs(1 / s->rayDir.x);
		s->deltaDist.y = fabs(1 / s->rayDir.y);
	}
}

static void	step(t_me *s, t_pos map)
{
	if (s->rayDir.x < 0)
	{
		s->step.x = -1;
		s->sideDist.x = (s->pos.x - map.x) * s->deltaDist.x;
	}
	else
	{
		s->step.x = 1;
		s->sideDist.x = (map.x + 1.0 - s->pos.x) * s->deltaDist.x;
	}
	if (s->rayDir.y < 0)
	{
		s->step.y = -1;
		s->sideDist.y = (s->pos.y - map.y) * s->deltaDist.y;
	}
	else
	{
		s->step.y = 1;
		s->sideDist.y = (map.y + 1.0 - s->pos.y) * s->deltaDist.y;
	}
}

static void	hit(t_set *s, t_pos *map, int *side)
{
	int			hit;

	hit = 0;
	while (hit == 0)
	{
		if (s->me->sideDist.x < s->me->sideDist.y)
		{
			s->me->sideDist.x += s->me->deltaDist.x;
			map->x += s->me->step.x;
			*side = 0;
		}
		else
		{
			s->me->sideDist.y += s->me->deltaDist.y;
			map->y += s->me->step.y;
			*side = 1;
		}
		if (s->mp[map->y][map->x] == '1')
			hit = 1;
	}
}

static void	draw(t_set *s, int x, int side)
{
	int			lineh;
	int			start;
	int			end;

	if (s->me->perp == 0)
		s->me->perp = 0.01;
	lineh = (int)(s->R[1] / s->me->perp);
	start = s->R[1] / 2 - lineh / 2;
	end = s->R[1] / 2 + lineh / 2;
	if (start < 0)
		start = 0;
	if (end > s->R[1])
		end = s->R[1];
	s->side = side;
	put_texture(s, x, start, end);
}

void	draw_wall(t_set *set, t_me *s)
{
	int		x;
	t_pos	map;
	int		side;
	double	zBuffer[5000];

	x = 0;
	while (x < set->R[0])
	{
		set_pos(&map, (int)s->pos.x, (int)s->pos.y);
		ray_position(set, s, x);
		step(s, map);
		hit(set, &map, &side);
		if (side == 0)
			s->perp = (map.x - s->pos.x + (1 - s->step.x) / 2) / s->rayDir.x;
		else
			s->perp = (map.y - s->pos.y + (1 - s->step.y) / 2) / s->rayDir.y;
		draw(set, x, side);
		zBuffer[x] = s->perp;
		x++;
	}
	draw_sprite(set, zBuffer, s);
}
