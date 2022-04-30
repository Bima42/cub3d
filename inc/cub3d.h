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

# define WALL '1'

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

//PARSING - parsing.c
int		parsing(char *path, t_game *game);
void	init_parse(t_parse *control);

//PARSING - collect_map.c
void	free_array(char **tab);
void	dup_array(char **tab, char **tmp);
char	**alloc_n_fill_array(char **tab);
char	**collect_map(char *line, int fd);

//PARSING - file_format.c
int		check_file_format(char *str, char *str2, int start);
int		file_format(char *path, t_parse *control);

//PARSING - game_infos.c
int		check_all_datas(t_game *game);
int		first_wall_line(char *line);
int		collect_data(char *line, t_game *game);
int		game_infos(t_game *game, t_parse *control);

//PARSING - tools.c
int		is_w_space(char c);
void	skip_white_space(char *str, int *i);
void	vertical_skip_white_space(char **str, int *i, int x, int max_i);

//PARSING - map_checker.c
int     check_map(char **map);

#endif
