/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:32 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/07 14:20:08 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_w_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	skip_white_space(char *str, int *i)
{
	if (!str)
		return ;
	while (is_w_space(str[*i]))
		*i += 1;
}

void	vertical_skip_white_space(char **str, int *i, int x)
{
	if (!str)
		return ;
	while (is_w_space(str[*i][x]) && str[*i][x])
		*i += 1;
}

void	free_array(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	dup_array(char **tab, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		tab[i] = ft_strdup(tmp[i]);
		if (!tab[i])
			exit_n_display("malloc failed\n");
		i++;
	}
	if (tmp)
		free_array(tmp);
}
