#include "../../inc/cub3d.h"

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
