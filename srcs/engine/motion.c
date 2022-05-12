#include "../../inc/cub3d.h"

void	move_if_allowed(t_game *game)
{
	int	new_map_x;
	int	new_map_y;

	new_map_x = game->player->next_x / (int)TILE;
	new_map_y = game->player->next_y / (int)TILE;
	if (game->map[new_map_y][new_map_x] != WALL)
	{
		game->player->x = game->player->next_x;
		game->player->y = game->player->next_y;
	}
}

void	player_rotation(t_game *game)
{
	if (game->keys->turnright)
		game->player->orientation += ROTATION;
	else if (game->keys->turnleft)
		game->player->orientation -= ROTATION;
}

void	player_move(t_game *game)
{
	if (game->keys->movefor)
	{
		game->player->next_x = game->player->x + cos(deg_to_rad(game->player->orientation)) * MOVESPEED;
		game->player->next_y = game->player->y - sin(deg_to_rad(game->player->orientation)) * MOVESPEED;
	}
	else if (game->keys->moveback)
	{
		game->player->next_x = game->player->x - cos(deg_to_rad(game->player->orientation)) * MOVESPEED;
		game->player->next_y = game->player->y + sin(deg_to_rad(game->player->orientation)) * MOVESPEED;
	}
	move_if_allowed(game);
	if (game->keys->moveright)
	{
		game->player->next_x = game->player->x + cos(deg_to_rad(game->player->orientation + 90)) * MOVESPEED;
		game->player->next_y = game->player->y - sin(deg_to_rad(game->player->orientation + 90)) * MOVESPEED;
	}
	else if (game->keys->moveleft)
	{
		game->player->next_x = game->player->x - cos(deg_to_rad(game->player->orientation + 90)) * MOVESPEED;
		game->player->next_y = game->player->y + sin(deg_to_rad(game->player->orientation + 90)) * MOVESPEED;
	}
	else if (game->keys->turnright || game->keys->turnleft)
		player_rotation(game);
	move_if_allowed(game);
}
