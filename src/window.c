#include "../cub3D.h"

void	clear_window(t_window *w)
{
	if (w->image->img)
		mlx_destroy_image(w->ptr, w->image->img);
	if (w->win)
		mlx_destroy_window(w->ptr, w->win);
	if (w->image)
		free(w->image);
	free(w);
}

void	update_image(t_window *w, t_image *i)
{
	mlx_put_image_to_window(w->ptr, w->win, i->img, 0, 0);
}

void	init_window(t_set *set, t_window *w, t_image *i)
{
	w->ptr = NULL;
	w->win = NULL;
	i->img = NULL;
	i->line_length = 10;
	i->bpp = 8;
	i->endian = 100;
	w->ptr = mlx_init();
	w->win = mlx_new_window(w->ptr, w->size.x, w->size.y, "cub3D");
	i->img = mlx_new_image(w->ptr, w->size.x, w->size.y);
	if (!w->ptr || !w->win || !i->img)
		error(set, "MLX problem");
}

void	init_image(t_set *set, t_window *w, t_image *i)
{
	i->img = mlx_new_image(w->ptr, w->size.x, w->size.y);
	if (!i->img)
		error(set, "MLX problem");
	i->addr = mlx_get_data_addr(i->img, &i->bpp, &i->line_length, &i->endian);
}
