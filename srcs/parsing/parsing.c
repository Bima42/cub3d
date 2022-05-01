#include "../../inc/cub3d.h"

void	init_parse(t_parse *control)
{
	control->fd = 0;
	control->spawn = 0;
	control->wall_err = 0;
	control->path_err = 0;
	control->id_err = 0;
	control->rgb_err = 0;
}

void	display_map(char **map)
{
	int	i = 0;

	while (map[i][0] != '\0')
		printf("%s\n", map[i++]);
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
	display_map(game->map);
	exit(1);
	return (1);
}
