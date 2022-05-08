/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:43:51 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/08 22:15:16 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	error_message(char *msg, int ret)
{
	write(1, msg, ft_strlen(msg));
	return (ret);
}

void	init_parse(t_parse *control)
{
	control->fd = 0;
	control->spawn = 0;
	control->wall_err = 0;
	control->path_err = 0;
	control->id_err = 0;
	control->rgb_err = 0;
}

int	check_data(t_texture_pack *pack, t_texture *texture, int count)
{
	char	**split;
	int		i;

	i = 0;
	if (count > 1)
		return (1);
	split = ft_split(texture->path, ',');
	if (!split)
		return (0);
	if (split[2])
	{
		texture->R = ft_atoi(split[0]);
		texture->G = ft_atoi(split[1]);
		texture->B = ft_atoi(split[2]);
	}
	if (texture->R < 0 || texture->R > 255)
		return (0);
	if (texture->G < 0 || texture->G > 255)
		return (0);
	if (texture->B < 0 || texture->B > 255)
		return (0);
	free_array(split);
	return (check_data(pack, pack->floor, ++count));
}

int	parsing(char *path, t_game *game)
{
	t_parse	control;

	init_parse(&control);
	if (!file_format(path, &control))
		return (error_message("File format error. Use .cub maps only\n", 0));
	if (!game_infos(game, &control))
		return (error_message("Datas might be missing, check data format and try again\n", 0));
	if (!check_data(game->texture_pack, game->texture_pack->ceiling, 0))
		return (error_message("Datas might be wrong, respect the format and try again\n", 0));
	if (!check_map(game->map, game, &control))
		return (error_message("A map error has been caught, make sure your map is valid and try again\n", 0));
	if (!check_texture_format(game))
		return (error_message("A texture format error has been detected, make sure the textures are .xpm\n", 0));
	return (1);
}
