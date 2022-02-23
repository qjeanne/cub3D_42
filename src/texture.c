#include "../cub3D.h"

void	new_texture(t_set *s, t_tex *t)
{
	t->ptr = mlx_xpm_file_to_image(s->window->ptr, t->path,
			&t->width, &t->height);
	if (!t->ptr)
		error(s, "MLX problem");
	t->addr = mlx_get_data_addr(t->ptr, &t->bpp, &t->line_length, &t->endian);
}

void	xmp_files(t_set *s)
{
	s->WE->ptr = 0;
	s->EA->ptr = 0;
	s->SO->ptr = 0;
	s->NO->ptr = 0;
	new_texture(s, s->EA);
	new_texture(s, s->WE);
	new_texture(s, s->SO);
	new_texture(s, s->NO);
	s->s_ptr = mlx_xpm_file_to_image(s->window->ptr, s->s_path,
			&s->s_width, &s->s_height);
	if (!s->s_ptr)
		error(s, "MLX problem");
	s->s_addr = mlx_get_data_addr(s->s_ptr, &s->s_bpp,
			 &s->s_line_length, &s->s_endian);
}

void	clear_tex(t_set *s)
{
	if (s->window && s->check == 1)
	{
		if (s->WE->ptr)
			mlx_destroy_image(s->window->ptr, s->WE->ptr);
		if (s->EA->ptr)
			mlx_destroy_image(s->window->ptr, s->EA->ptr);
		if (s->NO->ptr)
			mlx_destroy_image(s->window->ptr, s->NO->ptr);
		if (s->SO->ptr)
			mlx_destroy_image(s->window->ptr, s->SO->ptr);
		if (s->s_ptr)
			mlx_destroy_image(s->window->ptr, s->s_ptr);
	}
}

static int	tex_pos(t_set *s, int side)
{
	double		wallx;
	int			texx;

	if (side == 0)
		wallx = s->me->pos.y + s->me->perp * s->me->rayDir.y;
	else
		wallx = s->me->pos.x + s->me->perp * s->me->rayDir.x;
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)T_WIDTH);
	if (side == 0 && s->me->rayDir.x > 0)
		texx = T_WIDTH - texx - 1;
	else if (side == 1 && s->me->rayDir.y < 0)
		texx = T_WIDTH - texx - 1;
	return (texx);
}

void	put_texture(t_set *s, int x, int start, int end)
{
	int			color;
	double		texpos;
	int			texy;
	t_pos		p;
	void		*addr;

	addr = select_tex(s, s->side);
	texpos = (start - s->R[1] / 2 + (int)(s->R[1] / s->me->perp) / 2)
		* 1.0 * T_HEIGHT / (int)(s->R[1] / s->me->perp);
	while (start < end)
	{
		texy = (int)texpos & (T_HEIGHT - 1);
		texpos += 1.0 * T_HEIGHT / (int)(s->R[1] / s->me->perp);
		set_pos(&p, x, start);
		color = *(unsigned int *)((void *)(addr + (texy * s->WE->line_length
						+ tex_pos(s, s->side) * (s->WE->bpp / 8))));
		if (s->side == 1)
			color = (color >> 1) & 8355711;
		pixel(s->window->image, &p, color);
		start++;
	}
}
