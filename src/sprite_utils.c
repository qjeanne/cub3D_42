#include "../cub3D.h"

void	new_sprite(t_set *s, int x, int y)
{
	t_sprite	*new;

	new = (t_sprite *)malloc(sizeof(t_sprite));
	new->next = s->sprite;
	set_pos(&new->pos, x, y);
	s->sprite = new;
}

double	sprite_distance(t_sprite *s, t_p me)
{
	t_p		p;

	set_p(&p, (double)s->pos.x, (double)s->pos.y);
	return (sqrt(pow(p.x - me.x, 2) + pow(p.y - me.y, 2)));
}

void	sort_sprite(t_sprite *s, t_p me)
{
	t_sprite	*left;
	t_sprite	*right;
	t_pos		temp;

	left = s;
	right = s->next;
	while (left->next)
	{
		while (right)
		{
			if (sprite_distance(left, me) < (sprite_distance(right, me)))
			{
				set_pos(&temp, left->pos.x, left->pos.y);
				set_pos(&left->pos, right->pos.x, right->pos.y);
				set_pos(&right->pos, temp.x, temp.y);
			}
			right = right->next;
		}
		left = left->next;
		right = left->next;
	}
}
