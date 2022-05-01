#include "../inc/cub3d.h"

void	exit_n_display(char *str)
{
	write(1, str, ft_strlen(str));
	exit(0);
}

void	init_texture_pk_dir(t_game *game)
{
	t_texture	*no;
	t_texture	*so;
	t_texture	*ea;
	t_texture	*we;
	t_texture	*ceiling;
	t_texture	*floor;

	no = malloc(sizeof(t_texture));
	if (!no)
		exit_n_display("malloc failed\n");
	so = malloc(sizeof(t_texture));
	if (!so)
		exit_n_display("malloc failed\n");
	ea = malloc(sizeof(t_texture));
	if (!ea)
		exit_n_display("malloc failed\n");
	we = malloc(sizeof(t_texture));
	if (!we)
		exit_n_display("malloc failed\n");
	ceiling = malloc(sizeof(t_texture));
	if (!ceiling)
		exit_n_display("malloc failed\n");
	floor = malloc(sizeof(t_texture));
	if (!floor)
		exit_n_display("malloc failed\n");
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
	if (!texture_pack)
		exit_n_display("malloc failed\n");
	game->texture_pack = texture_pack;
	player = malloc(sizeof(t_player));
	if (!player)
		exit_n_display("malloc failed\n");
	game->player = player;
	init_texture_pk_dir(game);
	game->map = NULL;
	game->texture_pack->no->path = NULL;
	game->texture_pack->so->path = NULL;
	game->texture_pack->ea->path = NULL;
	game->texture_pack->we->path = NULL;
	game->texture_pack->ceiling->path = NULL;
	game->texture_pack->ceiling->R = 0;
	game->texture_pack->ceiling->G = 0;
	game->texture_pack->ceiling->B = 0;
	game->texture_pack->floor->path = NULL;
	game->texture_pack->floor->R = 0;
	game->texture_pack->floor->G = 0;
	game->texture_pack->floor->B = 0;
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
