/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:50:04 by tpauvret          #+#    #+#             */
/*   Updated: 2022/06/25 18:54:12 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	ft_bzero(&game->text.no, sizeof(t_texture));
	ft_bzero(&game->text.so, sizeof(t_texture));
	ft_bzero(&game->text.ea, sizeof(t_texture));
	ft_bzero(&game->text.we, sizeof(t_texture));
	ft_bzero(&game->text.floor, sizeof(t_texture));
	ft_bzero(&game->text.ceiling, sizeof(t_texture));
	ft_bzero(&game->text.exit, sizeof(t_texture));
	ft_bzero(&game->keys, sizeof(t_keys));
	ft_bzero(&game->p, sizeof(t_player));
	ft_bzero(&game->rays, sizeof(t_player));
}
