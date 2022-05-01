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

int	check_data(t_texture_pack *texture)
{
	int		i;
	char	*color;
}

int	parsing(char *path, t_game *game)
{
	t_parse	control;

	init_parse(&control);
	if (!file_format(path, &control))
		return (0);
	if (!game_infos(game, &control))
		return (0);
	if (!check_data(game->texture_pack))
		return (0);
	if (!check_map(game->map, game, &control))
		return (0);
	return (1);
}
