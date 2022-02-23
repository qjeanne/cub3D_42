NAME = cub3D

CC = gcc

FLAGS = -Wall -Werror -Wextra -fsanitize=undefined

FRAMEWORKS = -framework OpenGL -framework Appkit

INCLUDES = -I includes/ -I libft/

GNL_DIR =		gnl/
GNL_LIST =		get_next_line.c \
				get_next_line_utils.c \

SRC_DIR =		src/
SRC_LIST =		main.c \
				parser.c \
				getmap.c \
				ft_atoi.c \
				check.c \
				ft_strcmp.c \
				window.c \
				init.c \
				mlx_utils.c \
				draw.c \
				2dmap.c \
				key.c \
				position.c \
				wall.c \
				texture.c \
				parser_utils.c \
				sprite.c \
				sprite_utils.c \
				main_utils.c \
				screenshot.c \

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))
GNL = $(addprefix $(GNL_DIR), $(GNL_LIST))
SRCS = $(SRC) $(GNL)
OBJ = $(SRC:.c=.o) $(GNL:.c=.o)

LIBRARY = -L. -lmlx

all: $(NAME)
$(NAME): $(OBJ)
		make -C minilibx_opengl_20191021
		mv minilibx_opengl_20191021/libmlx.a .
		$(CC) $(FLAGS) $(SRCS) $(INCLUDES) $(LIBRARY) $(FRAMEWORKS) -o $(NAME)
		make clean
%.o: %.c
		gcc -g $(FLAGS) $(INCLUDES) -c $< -o $@
clean:
		rm -rf $(OBJ)
		rm -rf libmlx.a
fclean: clean
		make -C minilibx clean
		rm -rf $(NAME)
re: fclean all
run:
	./$(NAME)