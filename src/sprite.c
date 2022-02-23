#include "../cub3D.h"

static void	step1(t_set *s, t_sprite *tmp, t_me *me)
{
	double	spriteX;
	double	spriteY;
	double	transformX;
	double	invDet;

	spriteX = tmp->pos.x + 0.5 - me->pos.x;
	spriteY = tmp->pos.y + 0.5 - me->pos.y;
	invDet = 1.0 / (me->plane.x * me->dir.y - me->dir.x * me->plane.y);
	transformX = invDet * (me->dir.y * spriteX - me->dir.x * spriteY);
	tmp->transY = invDet * (-me->plane.y * spriteX + me->plane.x * spriteY);
	tmp->screenX = (int)((s->R[0] / 2) * (1 + transformX / tmp->transY));
}

static void	step2(t_set *s, t_sprite *tmp)
{
	tmp->h = abs((int)(s->R[1] / tmp->transY));
	tmp->start.y = -tmp->h / 2 + s->R[1] / 2;
	if (tmp->start.y < 0 )
		tmp->start.y = 0;
	tmp->end.y = tmp->h / 2 + s->R[1] / 2;
	if (tmp->end.y >= s->R[1])
		tmp->end.y = s->R[1] - 1;
	tmp->w = abs((int)(s->R[1] / tmp->transY));
	tmp->start.x = -tmp->w / 2 + tmp->screenX;
	if (tmp->start.x < 0)
		tmp->start.x = 0;
	tmp->end.x = tmp->w / 2 + tmp->screenX;
	if (tmp->end.x >= s->R[0])
		tmp->end.x = s->R[0] - 1;
}

static void	step3(t_set *s, t_sprite *tmp, int y, int texX)
{
	int		texY;
	int		d;
	int		color;
	t_pos	p;

	while (y < tmp->end.y)
	{
		d = y * 256 - s->R[1] * 128 + tmp->h * 128;
		texY = ((d * T_HEIGHT) / tmp->h) / 256;
		color = *(unsigned int *)((void *)(s->s_addr + (texY * s->s_line_length
						+ texX * (s->s_bpp / 8))));
		set_pos(&p, tmp->start.x, y);
		if ((color & 0x00FFFFFF) != 0)
			pixel(s->window->image, &p, color);
		y++;
	}
}

void	draw_sprite(t_set *s, double zBuffer[], t_me *me)
{
	t_sprite	*tmp;
	long int	texX;

	sort_sprite(s->sprite, s->me->pos);
	tmp = s->sprite;
	while (tmp != NULL)
	{
		step1(s, tmp, me);
		step2(s, tmp);
		while (tmp->start.x < tmp->end.x)
		{
			texX = (long int)(256 * (tmp->start.x - (-tmp->w / 2
							+ tmp->screenX)) * T_WIDTH / tmp->w) / 256;
			if (tmp->transY > 0 && tmp->start.x > 0 && tmp->start.x < s->R[0]
				&& tmp->transY < zBuffer[tmp->start.x])
				step3(s, tmp, tmp->start.y, texX);
			tmp->start.x++;
		}
		tmp = tmp->next;
	}
}
