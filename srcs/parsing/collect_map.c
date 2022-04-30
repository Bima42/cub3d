#include "../../inc/cub3d.h"

void	free_array(char **tab)
{
	int	i;

	i = -1;
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
		i++;
	}
	if (tmp)
		free_array(tmp);
}

char	**alloc_n_fill_array(char **tab)
{
	char	**ret;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	ret = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (tab[++i])
		ret[i] = ft_strdup(tab[i]);
	ret[i] = 0;
	return (ret);
}

char	**collect_map(char *line, int fd)
{
	char	**tab;
	char	**tmp;
	int		row;

	row = 0;
	tmp = NULL;
	tab = NULL;
	while (line)
	{
		if (tab)
		{
			tmp = alloc_n_fill_array(tab);
			free_array(tab);
		}
		tab = malloc(sizeof(char *) * ++row + 1);
		if (!tab)
			return (NULL);
		if (tmp)
			dup_array(tab, tmp);
		tab[row - 1] = ft_strdup(line);
		tab[row] = 0;
		free(line);
		line = get_next_line(fd);
	}
	return (tab);
}
