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

int	collect_data(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] != 32)
		i++;
	if (!ft_strncmp(line, "NO", i) && game->texture_pack->no->path == NULL)
		game->texture_pack->no->path = ft_substr(line, i + 1, ft_strlen(line) - i);
	else if (!ft_strncmp(line, "SO", i) && game->texture_pack->so->path == NULL)
		game->texture_pack->so->path = ft_substr(line, i + 1, ft_strlen(line) - i);
	else if (!ft_strncmp(line, "EA", i) && game->texture_pack->ea->path == NULL)
		game->texture_pack->ea->path = ft_substr(line, i + 1, ft_strlen(line) - i);
	else if (!ft_strncmp(line, "WE", i) && game->texture_pack->we->path == NULL)
		game->texture_pack->we->path = ft_substr(line, i + 1, ft_strlen(line) - i);
	else if (!ft_strncmp(line, "C", i) && game->texture_pack->ceiling->path == NULL)
		game->texture_pack->ceiling->path = ft_substr(line, i + 1, ft_strlen(line) - i);
	else if (!ft_strncmp(line, "F", i) && game->texture_pack->floor->path == NULL)
		game->texture_pack->floor->path = ft_substr(line, i + 1, ft_strlen(line) - i);
	else
		return (0);
	return (1);
}

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

int	game_infos(t_game *game, t_parse *control)
{
	char	*line;

	line = get_next_line(control->fd);
	if (!line)
		return (0);
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
		line = get_next_line(control->fd);
	}
	if (!check_all_datas(game))
		return (0);	// free en partant !
	game->map = collect_map(line, control->fd);
	return (1);
}


int	check_file_format(char *str, char *str2, int start)
{
	// cette fonction c'est un strcmp avec un start point
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

void	init_parse(t_parse *control)
{
	control->fd = 0;
	control->spawn = 0;
	control->wall_err = 0;
	control->path_err = 0;
	control->id_err = 0;
	control->rgb_err = 0;
}

int	check_first_line(char **map)
{
	int	i;
	int	flag_x;
	int	flag_y;
	int	row;

	i = 0;
	row = 0;
	flag_x = 0;
	flag_y = 0;
	while (map[row][i] == WALL || map[row][i] == 32)
	{
		if (map[row][i] == 32)
		{
			flag_y = row;
			while (map[row][i] == 32)
				row++;
			flag_x = i;
			skip_white_space(map[row - 1], &flag_x);
			while (map[row][i] == WALL && i != flag_x)
				i++;
			if (i == flag_x && map[row][i] == WALL)
				while (row != flag_y)
					row--;
			else
				return (0);
		}
		i++;
	}
	if (map[row][i] != '\0')
		return (0);
	return (1);
}

int	check_perimeter(char **map)
{
	int	len;
	int	start;
	int	row;

	len = 0;
	start = 0;
	row = 0;
	while (map[row])
	{
		skip_white_space(map[row], &start);
		len = ft_strlen(map[row]) - 1;
		if (map[row][start] != WALL || map[row][len] != WALL)
			return (0);
		row++;
		start = 0;
	}
	return (1);
}

int	check_map(char **map)
{
	if (!check_first_line(map))
		return (0);
//	if (!check_last_line(map))
//		return (0);
	if (!check_perimeter(map))
		return (0);
	return (1);
}

int	parsing(char *path, t_game *game)
{
	t_parse	control;

	init_parse(&control);
	if (!file_format(path, &control))
		return (0);
	if (!game_infos(game, &control))
		return (0);
	if (!check_map(game->map))
		return (0);
	return (1);
}
