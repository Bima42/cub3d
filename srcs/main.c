#include "../inc/cub3d.h"

void	init_game(t_game *game)
{
	game->map = NULL;
	game->texture_pack->no->path = NULL;
	game->texture_pack->so->path = NULL;
	game->texture_pack->ea->path = NULL;
	game->texture_pack->we->path = NULL;
	game->texture_pack->ceiling->path = NULL;
	game->texture_pack->floor->path = NULL;
	game->player = NULL;
}

int	main(int argc, char **argv)
{
	t_game	game;
	(void)argc;

	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	init_game(&game);
	parsing(argv[1], &game);
	return (0);
}
