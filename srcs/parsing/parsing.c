#include "../../inc/cub3d.h"

/*int	check_first_line(char **map)
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
}*/

/*int	check_map(char **map)
{
	if (!check_first_line(map))
		return (0);
//	if (!check_last_line(map))
//		return (0);
	if (!check_perimeter(map))
		return (0);
	return (1);
}*/

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
		return (0);
	if (!game_infos(game, &control))
		return (0);
//	if (!check_map(game->map))
//		return (0);
	return (1);
}
