/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:09 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/02 15:44:10 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_file_format(char *str, char *str2, int start)
{
	int	i;

	i = 0;
	while (str[start])
	{
		if (str[start] != str2[i])
			return (str[start] - str2[i]);
		else
		{
			start++;
			i++;
		}
	}
	return (0);
}

int	file_format(char *path, t_parse *control)
{
	int	size;

	size = ft_strlen(path);
	if (check_file_format(path, ".cub", size - 4))
		return (0);
	else
	{
		control->fd = open(path, O_RDONLY);
		if (control->fd < 0)
			return (0);
	}
	return (1);
}
