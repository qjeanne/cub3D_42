#ifndef CUB3D_H
# define CUB3D_H
# include "gnl/get_next_line.h"
# include "stdio.h"
# include "fcntl.h"
# include "math.h"
# include "minilibx_opengl_20191021/mlx.h"

# define ESC 53
# define W 13
# define A 0
# define SS 1
# define D 2
# define LEFT 123
# define RIGHT 124

# define SPEED 0.11
# define TURN 0.05

# define T_HEIGHT 64
# define T_WIDTH 64

# define BMP_HEADER 54
# define BMP_INFO_SIZE 40

typedef struct s_pos
{
	int		x;
	int		y;
}				t_pos;

typedef struct s_p
{
	double				x;
	double				y;
}						t_p;

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
}						t_image;

typedef struct s_sprite
{
	t_pos				pos;
	int					h;
	int					w;
	t_pos				start;
	t_pos				end;
	double				transY;
	int					screenX;
	struct s_sprite		*next;

}						t_sprite;

typedef struct s_window
{
	void				*ptr;
	void				*win;
	t_pos				size;
	t_image				*image;
}						t_window;

typedef struct s_me
{
	t_p					pos;
	t_p					plane;
	t_p					dir;
	double				cameraX;
	double				perp;
	t_p					rayDir;
	t_p					sideDist;
	t_p					deltaDist;
	t_p					step;
}						t_me;

typedef struct s_tex
{
	void				*ptr;
	char				*path;
	void				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_length;
	int					endian;
}						t_tex;

typedef struct s_set
{
	int					R[2];
	t_tex				*NO;
	t_tex				*SO;
	t_tex				*WE;
	t_tex				*EA;
	t_sprite			*sprite;
	int					F[3];
	int					C[3];
	char				*map;
	char				**mp;
	int					way;
	int					side;
	int					save;
	t_p					move;
	double				rotate;
	char				*s_path;
	void				*s_ptr;
	void				*s_addr;
	int					s_width;
	int					s_height;
	int					s_bpp;
	int					s_line_length;
	int					s_endian;
	t_me				*me;
	t_window			*window;
	int					check;
}						t_set;

void	parser(t_set *set, char *path);
int		ft_atoi(t_set *s, const char **str);
void	error(t_set *set, char *str);
char	*skip(char *str);
void	getmap(int *fd, char *str, t_set *set);
int		checkparam(t_set *set);
void	check(t_set *set);
int		ft_strcmp(const char *s1, const char *s2);
void	init_game(t_set *set);
void	init_window(t_set *set, t_window *w, t_image *i);
void	set_pos(t_pos *pos, int x, int y);
void	pixel(t_image *i, t_pos *start, int color);
int		rectangle(t_window *w, t_pos *p1, t_pos *p2, int color);
int		draw_map(t_set *s);
int		key_press(int key, t_set *s);
int		key_release(int key, t_set *s);
int		key_exit(t_set *s);
void	clear_window(t_window *w);
void	init_image(t_set *set, t_window *w, t_image *i);
void	update_image(t_window *w, t_image *i);
void	update_draw(t_set *s);
void	set_p(t_p *pos, double x, double y);
void	move_y(t_set *s, int way);
void	move_x(t_set *s, int way);
void	rotate(t_set *s, int way);
void	draw_wall(t_set *s, t_me *me);
void	xmp_files(t_set *s);
void	put_texture(t_set *s, int x, int start, int end);
void	clear_tex(t_set *s);
char	*skip_dot(t_set *set, char *line);
void	*select_tex(t_set *s, int side);
void	new_sprite(t_set *s, int x, int y);
void	draw_sprite(t_set *s, double zBuffer[], t_me *me);
void	free_path(t_set *set);
void	get_textures_take(t_set *set, char *copy, char *str, int size);
void	getF_take(t_set *set, int a, int b, int c);
void	getC_take(t_set *set, int a, int b, int c);
int		parser_util(t_set *set, char *path);
void	free_sprite(t_set *set);
void	sort_sprite(t_sprite *s, t_p me);
void	save_bmp(t_set *set);
void	color(t_set *set);

#endif
