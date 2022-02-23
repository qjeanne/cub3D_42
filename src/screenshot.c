#include "../cub3D.h"

static void	zero(unsigned char buf[], int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		buf[i] = (unsigned char) 0;
		i++;
	}
}

static void	in_header(t_set *s, int fd)
{
	unsigned int		size;
	unsigned char		header[BMP_HEADER];

	zero(header, BMP_HEADER);
	size = BMP_HEADER + s->window->size.x * s->window->size.y;
	header[0] = (unsigned char) 'B';
	header[1] = (unsigned char) 'M';
	header[2] = size;
	header[3] = size >> 8;
	header[4] = size >> 16;
	header[5] = size >> 24;
	header[10] = (unsigned char) BMP_HEADER;
	header[14] = (unsigned char) BMP_INFO_SIZE;
	header[18] = s->window->size.x;
	header[19] = s->window->size.x >> 8;
	header[20] = s->window->size.x >> 16;
	header[21] = s->window->size.x >> 24;
	header[22] = s->window->size.y;
	header[23] = s->window->size.y >> 8;
	header[24] = s->window->size.y >> 16;
	header[25] = s->window->size.y >> 24;
	header[26] = (unsigned char) 1;
	header[28] = (unsigned char) s->window->image->bpp;
	write(fd, header, BMP_HEADER);
}

void	save_bmp(t_set *set)
{
	int				fd;
	int				i;
	int				j;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY
			| O_TRUNC, S_IRWXU, S_IWRITE);
	if (fd == -1)
		error(set, "Create BMP problem");
	in_header(set, fd);
	i = set->window->size.y - 1;
	j = set->window->size.x * (set->window->image->bpp / 8);
	while (i >= 0)
	{
		write(fd,
			&set->window->image->addr[i * set->window->image->line_length], j);
		i--;
	}
	close(fd);
	error(set, NULL);
}
