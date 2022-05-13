/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:31:42 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/13 14:31:43 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	create_image(t_game *game)
{
	if (game->img->img != NULL)
		mlx_destroy_image(game->mlx, game->img->img);
	game->img->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bpp, &game->img->linelen, &game->img->endian);
}

void	draw_background(t_game *game)
{
	int				x;
	int				y;
	t_texture	color;

	y = -1;
	color.R = 0;
	color.G = 0;
	color.B = 0;
	define_color(&color, game->texture_pack->ceiling);
	while (++y < WIN_H)
	{
		x = -1;
		if (y == WIN_H / 2)
			define_color(&color, game->texture_pack->floor);
		while (++x < WIN_W)
			put_pixel(game->img, x, y, color_picker(color.R, color.G, color.B));
	}
}

int	engine(t_game *game)
{
	create_image(game);
	draw_background(game);
	player_move(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win->mlx_win, game->img->img, 0, 0);
	mlx_do_sync(game->mlx);
	return (0);
}
