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
# define NORTH 78
# define SOUTH 83
# define EAST 69
# define WEST 87

# define ESCAPE 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define Z 6
# define Q 12
# define S 1
# define D 0
# define W 13
# define A 2

typedef struct s_game
{
	char					**map;
	struct s_texture_pack	*texture_pack;
	struct s_player			*player;
    void                    *mlx;
    int                     w;
    int                     h;
    struct s_window         *win;
    struct s_keys           *keys;
}			t_game;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_window
{
	void                    *mlx_win;
    struct s_img            img;
}           t_window;

typedef struct	s_keys
{
	int			movefor;
	int			moveback;
	int			moveleft;
	int			moveright;
	int			turnleft;
	int			turnright;
}				t_keys;

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
	char	        *path;
    struct s_img    img;
	int		        R;
	int		        G;
	int		        B;
}			t_texture;

typedef struct s_player
{
	int	x;
	int	y;
	int	hp;
	int	orientation;
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
int     error_message(char *msg, int ret);

//PARSING - collect_map.c
void	realloc_string(char **map, int row, int len);
char	**format_map(char **map);
char	**alloc_n_fill_array(char **tab);
int		init_collect(int *row, char ***tmp, char ***tab, char *line);
char	**collect_map(char *line, int fd);

//PARSING - file_format.c
int		check_file_format(char *str, char *str2, int start);
int		file_format(char *path, t_parse *control);

//PARSING - game_infos.c
int		check_all_datas(t_game *game);
int		first_wall_line(char *line);
int		collect_data(char *l, t_game *game);
int		game_infos(t_game *game, t_parse *control);

//PARSING - tools.c
int		is_w_space(char c);
void	skip_white_space(char *str, int *i);
void	vertical_skip_white_space(char **str, int *i, int x);
void	free_array(char **tab);
void	dup_array(char **tab, char **tmp);

//PARSING - map_checker.c
int		control_axis_x(char **map, int y, int max_y);
int		control_axis_x(char **map, int x, int max_x);
void	get_max(char **map, int *max_y, int *max_x);
int		find_player_pos(char **map, t_game *game, t_parse *control);
int     check_map(char **map, t_game *game, t_parse *control);

//INIT - init.c
void	init_texture_pk_dir(t_game *game);
void	init_texture_pk_dir_next(t_game *game);
void	set_texture_pack(t_game *game);
void	init_game(t_game *game);

//MAIN - main.c
void	exit_n_display(char *str);
void	destroy_struct(t_game *game);

//VIDEO - video_init.c
void    load_tex(t_game *game);
void    load_tex_bis(t_game *game);
int     video_init(t_game *game);
void    check_dim(t_game *game);

//VIDEO - window_init.c
void    window_init(t_game *game);

//MAIN - hooks.c
void    set_hooks(t_game *game);
int     pressed(int keycode, t_keys *keys);
int     released(int keycode, t_keys *keys);

#endif
