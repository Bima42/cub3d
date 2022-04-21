# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../mlx/mlx.h"

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
