#include "../cub3D.h"

void	pixel(t_image *i, t_pos *start, int color)
{
	char	*dst;

	dst = i->addr + (start->y * i->line_length + start->x * (i->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	limit(t_pos *pos, t_pos *size)
{
	if (pos->y < 0)
		pos->y = 0;
	if (pos->y > size->y)
		pos->y = size->y - 1;
	if (pos->x < 0)
		pos->x = 0;
	if (pos->x > size->x)
		pos->x = size->x - 1;
}

int	rectangle(t_window *w, t_pos *p1, t_pos *p2, int color)
{
	int		i;
	int		j;
	t_pos	pos;

	limit(p1, &w->size);
	limit(p2, &w->size);
	i = p1->y;
	while (i < p2->y)
	{
		pos.y = i;
		j = p1->x;
		while (j < p2->x)
		{
			pos.x = j++;
			pixel(w->image, &pos, color);
		}
		i++;
	}
	return (1);
}
