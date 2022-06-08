/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:15 by tpauvret          #+#    #+#             */
/*   Updated: 2022/06/08 14:02:03 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_all_datas(t_game *game)
{
	if (game->text.no.path
		&& game->text.so.path
		&& game->text.we.path
		&& game->text.ea.path
		&& game->text.exit.path
		&& game->text.ceiling.path
		&& game->text.floor.path)
		return (1);
	return (0);
}

int	first_wall_line(char *line)
{
	int	i;

	i = 0;
	if (!line || line[0] == '\0')
		return (0);
	skip_white_space(line, &i);
	while (line[i] == WALL)
	{
		i++;
		skip_white_space(line, &i);
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	collect_data(char *l, t_game *game, int i)
{
	if (!l)
		return (0);
	while (l[i] != 32)
		i++;
	if (!ft_strncmp(l, "NO", i) && game->text.no.path == NULL)
		game->text.no.path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "SO", i) && game->text.so.path == NULL)
		game->text.so.path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "EA", i) && game->text.ea.path == NULL)
		game->text.ea.path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "WE", i) && game->text.we.path == NULL)
		game->text.we.path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "EX", i) && game->text.exit.path == NULL)
		game->text.exit.path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "C", i)
		&& game->text.ceiling.path == NULL)
		game->text.ceiling.path
			= ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "F", i) && game->text.floor.path == NULL)
		game->text.floor.path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else
		return (0);
	return (1);
}

int	game_infos(t_game *game, t_parse *control)
{
	char	*line;

	line = get_next_line(control->fd);
	while (!first_wall_line(line))
	{
		while (line[0] == '\0')
		{
			free(line);
			line = get_next_line(control->fd);
		}
		if (first_wall_line(line))
			break ;
		if (!collect_data(line, game, 0))
			return (0);
		free(line);
		line = get_next_line(control->fd);
	}
	if (!check_all_datas(game))
		return (0);
	game->map = collect_map(line, control->fd);
	if (!game->map)
		return (0);
	return (1);
}
