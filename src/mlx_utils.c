#include "../cub3D.h"

void	set_pos(t_pos *pos, int x, int y)
{
	pos->x = x;
	pos->y = y;
}

void	set_p(t_p *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}

void	draw_back(t_set *s)
{
	t_pos		a;
	t_pos		b;

	set_pos(&a, 0, 0);
	set_pos(&b, s->R[0], s->R[1]);
	rectangle(s->window, &a, &b, s->C[0]);
	set_pos(&a, 0, s->R[1] / 2);
	rectangle(s->window, &a, &b, s->F[0]);
}

void	*select_tex(t_set *s, int side)
{
	void	*addr;

	addr = NULL;
	if (side == 1 && s->me->step.y < 0)
		addr = s->NO->addr;
	else if (side == 1 && s->me->step.y > 0)
		addr = s->SO->addr;
	else if (side == 0 && s->me->step.x < 0)
		addr = s->EA->addr;
	else if (side == 0 && s->me->step.x > 0)
		addr = s->WE->addr;
	return (addr);
}

void	update_draw(t_set *s)
{
	mlx_destroy_image(s->window->ptr, s->window->image->img);
	init_image(s, s->window, s->window->image);
	draw_back(s);
	draw_wall(s, s->me);
	draw_map(s);
	update_image(s->window, s->window->image);
}
