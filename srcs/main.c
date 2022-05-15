/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:47:24 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/15 15:54:10 by tpauvret         ###   ########.fr       */
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
	free(game->text->no->path);
	free(game->text->so->path);
	free(game->text->ea->path);
	free(game->text->we->path);
	free(game->text->ceiling->path);
	free(game->text->floor->path);
	free(game->text->no);
	free(game->text->so);
	free(game->text->ea);
	free(game->text->we);
	free(game->text->ceiling);
	free(game->text->floor);
	free(game->text);
//	free(game->p);
//	free(game->rays);
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
		window_init(&game);
		set_hooks(&game);
	}
	else
		write(1, "Wrong arguments\n", 16);
	return (0);
}
