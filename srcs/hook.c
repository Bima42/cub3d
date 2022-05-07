#include "../inc/cub3d.h"

void	set_hooks(t_game *game)
{
	mlx_hook(game->win->mlx_win, 2, 1L << 0, pressed, &(game->keys));
	mlx_hook(game->win->mlx_win, 3, 1L << 1, released, &(game->keys));
	//mlx_loop_hook(game->win->mlx_win, RAYCAST BABE, &game);
	mlx_loop(game->mlx);
}

int	pressed(int keycode, t_keys *keys)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		keys->movefor = 1;
	if (keycode == 1)
		keys->moveback = 1;
	if (keycode == 0)
		keys->moveright = 1;
	if (keycode == 2)
		keys->moveleft = 1;
	if (keycode == 123)
		keys->turnright = 1;
	if (keycode == 124)
		keys->turnleft = 1;
	return (0);
}

int	released(int keycode, t_keys *keys)
{
	if (keycode == 13)
		keys->movefor = 0;
	if (keycode == 1)
		keys->moveback = 0;
	if (keycode == 0)
		keys->moveright = 0;
	if (keycode == 2)
		keys->moveleft = 0;
	if (keycode == 123)
		keys->turnright = 0;
	if (keycode == 124)
		keys->turnleft = 0;
	return (0);
}
