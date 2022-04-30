#include "../inc/cub3d.h"

void	init_texture_pk_dir(t_game *game)
{
	t_texture	*no;
	t_texture	*so;
	t_texture	*ea;
	t_texture	*we;
	t_texture	*ceiling;
	t_texture	*floor;

	no = malloc(sizeof(t_texture));
	so = malloc(sizeof(t_texture));
	ea = malloc(sizeof(t_texture));
	we = malloc(sizeof(t_texture));
	ceiling = malloc(sizeof(t_texture));
	floor = malloc(sizeof(t_texture));
	game->texture_pack->no = no;
	game->texture_pack->so = so;
	game->texture_pack->ea = ea;
	game->texture_pack->we = we;
	game->texture_pack->ceiling = ceiling;
	game->texture_pack->floor = floor;
}

void	init_game(t_game *game)
{
	t_texture_pack	*texture_pack;
	t_player		*player;

	texture_pack = malloc(sizeof(t_texture_pack));
	game->texture_pack = texture_pack;
	player = malloc(sizeof(t_player));
	game->player = player;
	init_texture_pk_dir(game);
	game->map = NULL;
	game->texture_pack->no->path = NULL;
	game->texture_pack->so->path = NULL;
	game->texture_pack->ea->path = NULL;
	game->texture_pack->we->path = NULL;
	game->texture_pack->ceiling->path = NULL;
	game->texture_pack->floor->path = NULL;
	game->player->x = 0;
	game->player->y = 0;
	game->player->hp = 0;
}

void	destroy_struct(t_game *game)
{
	free_array(game->map);
	free(game->texture_pack->no->path);
	free(game->texture_pack->so->path);
	free(game->texture_pack->ea->path);
	free(game->texture_pack->we->path);
	free(game->texture_pack->ceiling->path);
	free(game->texture_pack->floor->path);
	free(game->texture_pack->no);
	free(game->texture_pack->so);
	free(game->texture_pack->ea);
	free(game->texture_pack->we);
	free(game->texture_pack->ceiling);
	free(game->texture_pack->floor);
	free(game->texture_pack);
	free(game->player);
	free(game);
}

int	main(int argc, char **argv)
{
	t_game	game;
	(void)argc;

	init_game(&game);
	if (!parsing(argv[1], &game))
		printf("Error\n");
	return (0);
}
