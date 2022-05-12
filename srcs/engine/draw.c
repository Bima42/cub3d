#include "../../inc/cub3d.h"

void	draw_wall(t_game *game)
{
	if (game->texture_pack->wall == game->texture_pack->so
		|| game->texture_pack->wall == game->texture_pack->we)
		game->rays->text_x = WALL_RES - game->rays->text_x;
	while (game->start < game->end)
	{
		game->rays->text_y = (game->start - game->player->height + game->rays->length / 2) * WALL_RES / game->rays->length;
		//game->color = get_pixel(game, game->rays->text_x, game->rays->text_y);
		if (game->flag_hori)
			game->color = color_picker(23, 198, 210);
		else
			game->color = color_picker(209, 24, 191);
		put_pixel(game->img, game->column, game->start, game->color);
		game->start++;
	}
}

void	draw(t_game *game)
{
	game->rays->dist *= cos(deg_to_rad(game->player->orientation - game->rays->ang));
	game->rays->length = RATIO / game->rays->dist;
	game->start = game->player->height - game->rays->length / 2 + 1;
	game->end = game->player->height + game->rays->length / 2;
	game->start = (game->start < 0 ? 0 : game->start);
	game->end = (game->end >= WIN_H ? (WIN_H - 1) : game->end);
	if (game->flag_hori)
	{
		game->rays->text_x = fmod(game->rays->h_hit_x, TILE);
		if (game->rays->ang > EAST && game->rays->ang < WEST)
			game->texture_pack->wall = game->texture_pack->no;
		else
			game->texture_pack->wall = game->texture_pack->so;
	}
	else
	{
		game->rays->text_x = fmod(game->rays->v_hit_y, TILE);
		if (game->rays->ang >= NORTH && game->rays->ang <= SOUTH)
			game->texture_pack->wall = game->texture_pack->we;
		else
			game->texture_pack->wall = game->texture_pack->ea;
	}
	draw_wall(game);
}
