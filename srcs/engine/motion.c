/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:31:54 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/20 19:22:20 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_if_allowed(t_game *game)
{
	int	new_map_x;
	int	new_map_y;

	new_map_x = game->p.next_x / (int)TILE;
	new_map_y = game->p.next_y / (int)TILE;
	if (game->map[new_map_y][new_map_x] != WALL)
	{
		if (game->map[new_map_y][new_map_x] == 'Q')
		{
			destroy_struct(game, "END\n");
			exit(0);
		}
		game->p.x = game->p.next_x;
		game->p.y = game->p.next_y;
	}
}

void	player_rotation(t_game *game)
{
	if (game->keys.turnright)
		game->p.vis += ROTATION;
	else if (game->keys.turnleft)
		game->p.vis -= ROTATION;
}

void	player_move(t_game *game)
{
	if (game->keys.movefor)
	{
		game->p.next_x = game->p.x + cos(deg_to_rad(game->p.vis)) * MS;
		game->p.next_y = game->p.y - sin(deg_to_rad(game->p.vis)) * MS;
	}
	else if (game->keys.moveback)
	{
		game->p.next_x = game->p.x - cos(deg_to_rad(game->p.vis)) * MS;
		game->p.next_y = game->p.y + sin(deg_to_rad(game->p.vis)) * MS;
	}
	move_if_allowed(game);
	if (game->keys.moveright)
	{
		game->p.next_x = game->p.x + cos(deg_to_rad(game->p.vis + 90)) * MS;
		game->p.next_y = game->p.y - sin(deg_to_rad(game->p.vis + 90)) * MS;
	}
	else if (game->keys.moveleft)
	{
		game->p.next_x = game->p.x - cos(deg_to_rad(game->p.vis + 90)) * MS;
		game->p.next_y = game->p.y + sin(deg_to_rad(game->p.vis + 90)) * MS;
	}
	else if (game->keys.turnright || game->keys.turnleft)
		player_rotation(game);
	move_if_allowed(game);
}
