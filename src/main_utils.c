#include "../cub3D.h"

void	free_path(t_set *set)
{
	if (set->NO->path)
		free(set->NO->path);
	free(set->NO);
	if (set->SO->path)
		free(set->SO->path);
	free(set->SO);
	if (set->WE->path)
		free(set->WE->path);
	free(set->WE);
	if (set->EA->path)
		free(set->EA->path);
	free(set->EA);
	if (set->s_path)
		free(set->s_path);
}

void	new_RGB(t_set *new)
{
	new->R[0] = 0;
	new->R[1] = 0;
	new->F[0] = -1;
	new->F[1] = -1;
	new->F[2] = -1;
	new->C[0] = -1;
	new->C[1] = -1;
	new->C[2] = -1;
}

void	free_sprite(t_set *set)
{
	t_sprite	*tmp;

	while (set->sprite != NULL)
	{
		tmp = set->sprite->next;
		free(set->sprite);
		set->sprite = tmp;
	}
}
