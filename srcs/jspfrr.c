#include "../inc/cub3d.h"

/*void	texture_loader(t_game *game)
{
	// IT'S FROM SO LONG I DID NOT CHANGE A SINGLE THING
	load_one_texture(*game, &(*game)->sprite.player_1, "./img/player_1.xpm");
}

void	destroy_mlx(t_game *game)
{
	mlx_destroy_image(game->mlx, game->);
}*/

void	create_window(t_game *game)
{
	game->win->x = 1920;
	game->win->y = 1024;
	exit(0);
	game->win->mlx_win = mlx_new_window(game->mlx,
			game->win->x, game->win->y, "cub3d");
	game->win->img = mlx_new_image(game->mlx,
			game->win->x, game->win->y);
}

void	init_win(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	game->mlx = mlx_init();
	create_window(game);
	mlx_put_image_to_window(game->mlx, game->win->mlx_win, game->win->img, x, y);
	mlx_loop(game->mlx);
}
