#include "../../inc/cub3d.h"

void	create_image(t_game *game)
{
	if (game->img->img != NULL)
		mlx_destroy_image(game->mlx, game->img->img);
	game->img->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bpp, &game->img->linelen, &game->img->endian);
}

void	define_color(t_texture *color, t_texture *zone)
{
	color->R = zone->R;
	color->G = zone->G;
	color->B = zone->B;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->linelen + x * (img->bpp / 8));
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	draw_background(t_game *game)
{
	int				x;
	int				y;
	t_texture	color;

	y = -1;
	color.R = 0;
	color.G = 0;
	color.B = 0;
	define_color(&color, game->texture_pack->ceiling);
	while (y++ < WIN_H)
	{
		x = -1;
		if (y == WIN_H / 2)
			define_color(&color, game->texture_pack->floor);
		while (x++ < WIN_W)
			put_pixel(game->img, x, y, color_picker(color.R, color.G, color.B));
	}
}

int	engine(t_game *game)
{
	create_image(game);
	draw_background(game);
	mlx_put_image_to_window(game->mlx, game->win->mlx_win, game->img->img, 0, 0);
	return (0);
}
