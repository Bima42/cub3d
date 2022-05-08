/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:50:04 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/08 14:42:09 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_texture_pk_dir(t_game *game)
{
	t_texture	*no;
	t_texture	*so;
	t_texture	*ea;

	no = malloc(sizeof(t_texture));
	if (!no)
		exit_n_display("malloc failed\n");
	so = malloc(sizeof(t_texture));
	if (!so)
		exit_n_display("malloc failed\n");
	ea = malloc(sizeof(t_texture));
	if (!ea)
		exit_n_display("malloc failed\n");
	game->texture_pack->no = no;
	game->texture_pack->so = so;
	game->texture_pack->ea = ea;
}

void	init_texture_pk_dir_next(t_game *game)
{
	t_texture	*we;
	t_texture	*ceiling;
	t_texture	*floor;

	we = malloc(sizeof(t_texture));
	if (!we)
		exit_n_display("malloc failed\n");
	ceiling = malloc(sizeof(t_texture));
	if (!ceiling)
		exit_n_display("malloc failed\n");
	floor = malloc(sizeof(t_texture));
	if (!floor)
		exit_n_display("malloc failed\n");
	game->texture_pack->we = we;
	game->texture_pack->ceiling = ceiling;
	game->texture_pack->floor = floor;
}

void	set_texture_pack(t_game *game)
{
	game->map = NULL;
	game->texture_pack->no->path = NULL;
	game->texture_pack->so->path = NULL;
	game->texture_pack->ea->path = NULL;
	game->texture_pack->we->path = NULL;
	game->texture_pack->ceiling->path = NULL;
	game->texture_pack->ceiling->R = 0;
	game->texture_pack->ceiling->G = 0;
	game->texture_pack->ceiling->B = 0;
	game->texture_pack->floor->path = NULL;
	game->texture_pack->floor->R = 0;
	game->texture_pack->floor->G = 0;
	game->texture_pack->floor->B = 0;
	game->player->x = 0;
	game->player->y = 0;
	game->player->hp = 0;
}

void	init_keys(t_game *game)
{
	t_keys *new;

	new = malloc(sizeof(t_keys));
	new->movefor = 0;
	new->moveback = 0;
	new->moveleft = 0;
	new->moveright = 0;
	new->turnleft = 0;
	new->turnright = 0;
	game->keys = new;
}

void	init_game(t_game *game)
{
	t_texture_pack	*texture_pack;
	t_player		*player;
	t_window		*window;

	init_keys(game);
	window = malloc(sizeof(t_window));
	if (!window)
		exit_n_display("malloc failed\n");
	game->win = window;
	texture_pack = malloc(sizeof(t_texture_pack));
	if (!texture_pack)
		exit_n_display("malloc failed\n");
	game->texture_pack = texture_pack;
	player = malloc(sizeof(t_player));
	if (!player)
		exit_n_display("malloc failed\n");
	game->player = player;
	init_texture_pk_dir(game);
	init_texture_pk_dir_next(game);
	set_texture_pack(game);
}
