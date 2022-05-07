#include "../../inc/cub3d.h"

void	load_tex(t_game *game)
{
	if (!(game->texture_pack->no->img.img = mlx_xpm_file_to_image(game->mlx, game->texture_pack->no->path,
		&game->texture_pack->no->img.width, &game->texture_pack->no->img.height)))
		exit_n_display("Failed to allocate north texture.\n");
	free(game->texture_pack->no->path);
	game->texture_pack->no->img.addr = mlx_get_data_addr(game->texture_pack->no->img.img,
			&game->texture_pack->no->img.bpp,
			&game->texture_pack->no->img.linelen, &game->texture_pack->no->img.endian);

	if (!(game->texture_pack->so->img.img = mlx_xpm_file_to_image(game->mlx, game->texture_pack->so->path,
		&game->texture_pack->so->img.width, &game->texture_pack->so->img.height)))
		exit_n_display("Failed to allocate south texture.\n");
	free(game->texture_pack->so->path);
	game->texture_pack->so->img.addr = mlx_get_data_addr(game->texture_pack->so->img.img,
			&game->texture_pack->so->img.bpp,
			&game->texture_pack->so->img.linelen, &game->texture_pack->so->img.endian);
}

void	load_tex_bis(t_game *game)
{
	if (!(game->texture_pack->we->img.img = mlx_xpm_file_to_image(game->mlx, game->texture_pack->we->path,
		&game->texture_pack->we->img.width, &game->texture_pack->we->img.height)))
		exit_n_display("Failed to allocate west texture.\n");
	free(game->texture_pack->we->path);
	game->texture_pack->we->img.addr = mlx_get_data_addr(game->texture_pack->we->img.img,
			&game->texture_pack->we->img.bpp,
			&game->texture_pack->we->img.linelen, &game->texture_pack->we->img.endian);

	if (!(game->texture_pack->ea->img.img = mlx_xpm_file_to_image(game->mlx, game->texture_pack->ea->path,
		&game->texture_pack->ea->img.width, &game->texture_pack->ea->img.height)))
		exit_n_display("Failed to allocate east texture.\n");
	free(game->texture_pack->ea->path);
	game->texture_pack->ea->img.addr = mlx_get_data_addr(game->texture_pack->ea->img.img,
			&game->texture_pack->ea->img.bpp,
			&game->texture_pack->ea->img.linelen, &game->texture_pack->ea->img.endian);
}

void	check_dim(t_game *game)
{
	if (!(game->texture_pack->no->img.width == game->texture_pack->no->img.height
			&& game->texture_pack->no->img.height == game->texture_pack->so->img.width
			&& game->texture_pack->so->img.width == game->texture_pack->so->img.height
			&& game->texture_pack->so->img.height == game->texture_pack->ea->img.width
			&& game->texture_pack->ea->img.width == game->texture_pack->ea->img.height
			&& game->texture_pack->ea->img.height == game->texture_pack->we->img.width
			&& game->texture_pack->we->img.width == game->texture_pack->we->img.height))
			exit_n_display("The textures do not possess the same dimensions.\n");
}

int	video_init(t_game *game)
{
	load_tex(game);
	load_tex_bis(game);
	check_dim(game);
	return (1);
}
