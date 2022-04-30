NAME = cub3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = libft/

LIBFT_LIB = $(LIBFT_PATH)libft.a

#MLX_PATH = mlx/

#MLX_LIB = $(MLX_PATH)libmlx.a

#MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework Appkit

SRCS = 	srcs/main.c \
		srcs/parsing/parsing.c \
		srcs/parsing/collect_map.c \
		srcs/parsing/file_format.c \
		srcs/parsing/game_infos.c \
		srcs/parsing/tools.c \
		srcs/parsing/map_checker.c \
		srcs/get_next_line/get_next_line.c \
		srcs/get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: subsystems $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

subsystems:
	make -C $(LIBFT_PATH) all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
