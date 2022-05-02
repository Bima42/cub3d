/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:15 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/02 21:30:04 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_all_datas(t_game *game)
{
	if (game->texture_pack->no->path
		&& game->texture_pack->so->path
		&& game->texture_pack->we->path
		&& game->texture_pack->ea->path
		&& game->texture_pack->ceiling->path
		&& game->texture_pack->floor->path)
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

//char *line est devenu *l, norm trick
int	collect_data(char *l, t_game *game)
{
	int	i;

	i = 0;
	if (!l)
		return (0);
	while (l[i] != 32)
		i++;
	if (!ft_strncmp(l, "NO", i) && game->texture_pack->no->path == NULL)
		game->texture_pack->no->path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "SO", i) && game->texture_pack->so->path == NULL)
		game->texture_pack->so->path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "EA", i) && game->texture_pack->ea->path == NULL)
		game->texture_pack->ea->path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "WE", i) && game->texture_pack->we->path == NULL)
		game->texture_pack->we->path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "C", i)
		&& game->texture_pack->ceiling->path == NULL)
		game->texture_pack->ceiling->path
			= ft_substr(l, i + 1, ft_strlen(l) - i);
	else if (!ft_strncmp(l, "F", i) && game->texture_pack->floor->path == NULL)
		game->texture_pack->floor->path = ft_substr(l, i + 1, ft_strlen(l) - i);
	else
		return (0);
	return (1);
}

int	game_infos(t_game *game, t_parse *control)
{
	char	*line;

	line = get_next_line(control->fd); // no need to be protected since if there is no line it will get catched in func. collect_data
	while (!first_wall_line(line))
	{
		while (line[0] == '\0')
		{
			free(line);
			line = get_next_line(control->fd);
		}
		if (first_wall_line(line))
			break ;
		if (!collect_data(line, game))
			return (0);
		free(line);
		line = get_next_line(control->fd); //NO NEED PROTECT ? ALL FUNC ARE PROTECTED
	}
	if (!check_all_datas(game))
		return (0); // free en partant !
	game->map = collect_map(line, control->fd);
	if (!game->map)
		return (0);
	return (1);
}
