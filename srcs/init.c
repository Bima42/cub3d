/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:50:04 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/20 18:33:40 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_texture	*init_texture(void)
{
	t_texture	*new;

	new = malloc(sizeof(t_texture));
	if (!new)
		exit_n_display("malloc failed\n");
	return (new);
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
	game->text->no = init_texture();
	game->text->so = init_texture();
	game->text->ea = init_texture();
	game->text->we = init_texture();
	game->text->exit = init_texture();
	game->text->floor = init_texture();
	game->text->ceiling = init_texture();
	ft_bzero(&game->keys, sizeof(t_keys));
	ft_bzero(&game->p, sizeof(t_player));
	ft_bzero(&game->rays, sizeof(t_player));
	set_texture_pack(game);
}
