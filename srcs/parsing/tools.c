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
	while (is_w_space(str[*i]))
		*i += 1;
}

void	vertical_skip_white_space(char **str, int *i, int x)
{
	while (is_w_space(str[*i][x]) && str[*i][x])
		*i += 1;
}

void	free_array(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
