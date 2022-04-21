NAME = cub3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

#MLX_PATH = mlx/

#MLX_LIB = $(MLX_PATH)libmlx.a

#MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework Appkit

SRCS = 	srcs/main.c \
		srcs/parsing.c \
		srcs/get_next_line/get_next_line.c \
		srcs/get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
