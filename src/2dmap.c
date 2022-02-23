#include "../cub3D.h"

static void	player(t_set *s, int len, int indent)
{
	t_pos	p1;
	t_pos	p2;
	double	x;
	double	y;

	x = (s->me->pos.x - 0.5) * len + indent;
	y = (s->me->pos.y - 0.5) * len + indent;
	set_pos(&p1, (int)x, (int)y);
	x = (s->me->pos.x + 0.5) * len + indent;
	y = (s->me->pos.y + 0.5) * len + indent;
	set_pos(&p2, (int)x, (int)y);
	rectangle(s->window, &p1, &p2, (100 << 16 | 10 << 8 | 10));
}

static void	draw(t_set *s, t_pos *p1, t_pos *p2, int len)
{
	int		i;
	int		j;
	int		indent;

	i = 0;
	j = 0;
	indent = p1->x;
	while (s->mp[i][0] != '\0')
	{
		while (s->mp[i][j] != '\0')
		{
			if (s->mp[i][j] == '1')
				rectangle(s->window, p1, p2, (100 << 16 | 100 << 8 | 100));
			else if (s->mp[i][j] == '2')
				rectangle(s->window, p1, p2, (50 << 16 | 100 << 8 | 100));
			p1->x += len;
			p2->x += len;
			j++;
		}
		set_pos(p1, indent, p1->y + len);
		set_pos(p2, indent + len, p2->y + len);
		i++;
		j = 0;
	}
	player(s, len, indent);
}

int	draw_map(t_set *s)
{
	int		indent;
	int		len;
	t_pos	pos1;
	t_pos	pos2;

	indent = s->R[0] / 80;
	len = s->R[0] * 0.008;
	set_pos(&pos1, indent, indent);
	set_pos(&pos2, indent + len, indent + len);
	draw(s, &pos1, &pos2, len);
	return (0);
}
