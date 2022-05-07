/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:47:24 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/07 17:36:12 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	exit_n_display(char *str)
{
	write(1, str, ft_strlen(str));
	exit(0);
}

void	destroy_struct(t_game *game)
{
	free_array(game->map);
	free(game->texture_pack->no->path);
	free(game->texture_pack->so->path);
	free(game->texture_pack->ea->path);
	free(game->texture_pack->we->path);
	free(game->texture_pack->ceiling->path);
	free(game->texture_pack->floor->path);
	free(game->texture_pack->no);
	free(game->texture_pack->so);
	free(game->texture_pack->ea);
	free(game->texture_pack->we);
	free(game->texture_pack->ceiling);
	free(game->texture_pack->floor);
	free(game->texture_pack);
	free(game->player);
	free(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.mlx = mlx_init();
	if (argc == 2)
	{
		init_game(&game);
		if (!parsing(argv[1], &game))
			exit_n_display("Error\n");
		video_init(&game);
	}
	else
		write(1, "Wrong arguments\n", 16);
	return (0);
}
