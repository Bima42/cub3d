#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../mlx/mlx.h"
# include "../srcs/get_next_line/get_next_line.h"
# include "../libft/libft.h"

# define WALL 1

typedef struct s_game
{
	char					**map;
	struct s_texture_pack	*texture_pack;
	struct s_player			*player;
}			t_game;

typedef struct s_texture_pack
{
	struct s_texture *no;
	struct s_texture *so;
	struct s_texture *ea;
	struct s_texture *we;
	struct s_texture *ceiling;
	struct s_texture *floor;
}			t_texture_pack;

typedef struct s_texture
{
	char	*path;
}			t_texture;

typedef struct s_player
{
	int	x;
	int	y;
	int	hp;
}			t_player;

typedef struct s_parse
{
    int fd;
    int spawn;
    int wall_err;
    int path_err;
    int id_err;
    int rgb_err;
}           t_parse;

//PARSING
int	parsing(char *path, t_game *game);

#endif
