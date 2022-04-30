#include "../../inc/cub3d.h"

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

void	realloc_string(char **map, int row, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		return ; // TODO : protect crash with exit func
	while (map[row][i])
	{
		tmp[i] = map[row][i];
		i++;
	}
	free(map[row]);
	while (i < len)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	map[row] = ft_strdup(tmp);
	free(tmp);
}

char	**format_map(char **map)
{
	int	max_x;
	int	max_y;
	int	i;
	int	len;

	max_x = 0;
	max_y = 0;
	get_max(map, &max_x, &max_y);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < max_y)
			realloc_string(map, i, max_y);
		i++;
	}
	return (map);
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
	return (format_map(tab));
}
