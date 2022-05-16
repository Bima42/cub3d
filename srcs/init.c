/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:50:04 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/16 12:20:20 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_texture_pk_dir(t_game *game)
{
	t_texture	*no;
	t_texture	*so;
	t_texture	*ea;
	t_texture	*we;

	no = malloc(sizeof(t_texture));
	if (!no)
		exit_n_display("malloc failed\n");
	so = malloc(sizeof(t_texture));
	if (!so)
		exit_n_display("malloc failed\n");
	ea = malloc(sizeof(t_texture));
	if (!ea)
		exit_n_display("malloc failed\n");
	we = malloc(sizeof(t_texture));
	if (!we)
		exit_n_display("malloc failed\n");
	game->text->no = no;
	game->text->so = so;
	game->text->ea = ea;
	game->text->we = we;
}

void	init_texture_pk_dir_next(t_game *game)
{
	t_texture	*ceiling;
	t_texture	*floor;

	ceiling = malloc(sizeof(t_texture));
	if (!ceiling)
		exit_n_display("malloc failed\n");
	floor = malloc(sizeof(t_texture));
	if (!floor)
		exit_n_display("malloc failed\n");
	game->text->ceiling = ceiling;
	game->text->floor = floor;
}

void	set_texture_pack(t_game *game)
{
	game->map = NULL;
	game->text->no->path = NULL;
	game->text->so->path = NULL;
	game->text->ea->path = NULL;
	game->text->we->path = NULL;
	game->text->ceiling->path = NULL;
	game->text->ceiling->r = 0;
	game->text->ceiling->g = 0;
	game->text->ceiling->b = 0;
	game->text->floor->path = NULL;
	game->text->floor->r = 0;
	game->text->floor->g = 0;
	game->text->floor->b = 0;
}

void	init_game(t_game *game)
{
	t_texture_pack	*texture_pack;

	texture_pack = malloc(sizeof(t_texture_pack));
	if (!texture_pack)
		exit_n_display("malloc failed\n");
	game->text = texture_pack;
	ft_bzero(&game->keys, sizeof(t_keys));
	ft_bzero(&game->p, sizeof(t_player));
	ft_bzero(&game->rays, sizeof(t_player));
	init_texture_pk_dir(game);
	init_texture_pk_dir_next(game);
	set_texture_pack(game);
}
