#include "../../inc/cub3d.h"

void	window_init(t_game *game)
{
	game->win->mlx_win = mlx_new_window(game->mlx, game->w, game->h, "cub3d");
	game->win->img.img = mlx_new_image(game->mlx, game->w, game->h);
	game->win->img.addr = mlx_get_data_addr(game->win->img.img,
			&game->win->img.bpp, &game->win->img.linelen, &game->win->img.endian);
}