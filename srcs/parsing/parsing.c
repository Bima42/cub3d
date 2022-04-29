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
	if (!line)
		return (0);
	skip_white_space(line, &i);
	while (line[i] == WALL)
	{
		i++;
		skip_white_space(line, &i);
		// petit trick si le haut de la map ressemble a ca :
		// 1111111     1111 1111111 11111
		// 100000111111100111000001110001
		// 100000000000000000000000000001
		// 100000000000000000000000000001
	}
	if (line[i] == '\0')
		return (1);
	return (0);
	// Dans cette fonction je skip les w space et apres je veux que des 1. si
	// il y a autre chose c'est pas considerer comme un mur
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
	return (0);
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

int	game_infos(t_game *game, t_parse *control)
{
	char	*line;

	line = get_next_line(control->fd);
	if (!line)
		return (0);
	while (!first_wall_line(line))
	{
		while (line[0] == '\n')
		{
			free(line);
			line = get_next_line(control->fd);
		}
		if (first_wall_line(line))
			break ;
		collect_data(line, game);
		free(line);
		line = get_next_line(control->fd);
	}
	if (!check_all_datas(game))
		return (0);	// free en partant !
	game->map[0] = line; // on stock la ligne qui a ete detectee si c'est le premiere wall
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

int	parsing(char *path, t_game *game)
{
	t_parse	control;

	init_parse(&control);
	if (!file_format(path, &control))
		return (1);
	if (!game_infos(game, &control))
		return (1);
//	if (!collect_map())
//		return (1);
	return (0);
}
