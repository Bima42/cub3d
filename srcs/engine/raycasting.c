#include "../../inc/cub3d.h"

double	degrees_to_radians(double value)
{
	return (value * M_PI / 180);
}

double	square(double value)
{
	return (value * value);
}

//see doc to understand this algo
void	digital_differential_analyzer(t_game *game)
{
	game->map_pos_x = game->rays->hit_x / (int)TILE;
	game->map_pos_y = game->rays->hit_y / (int)TILE;
	while (game->map_pos_x > 0 && game->map_pos_x < game->map_w
		&& game->map_pos_y > 0 && game->map_pos_y < game->map_h
		&& game->map[game->map_pos_y][game->map_pos_x] != '1')
	{
		game->rays->hit_x += game->rays->step_x;
		game->rays->hit_y += game->rays->step_y;
		game->map_pos_x = game->rays->hit_x / (int)TILE;
		game->map_pos_y = game->rays->hit_y / (int)TILE;
	}
}

double	vertical_raycasting(t_game *game)
{
	game->rays->tan = tan(degrees_to_radians(game->rays->ang));
	if (game->rays->ang < NORTH || game->rays->ang > SOUTH) // LOOKING RIGHT
	{
		game->rays->step_x = TILE;
		game->rays->hit_x = floor(game->player->x / TILE) * TILE + TILE; //Rounded down float to double
	//	game->rays->hit_x = floor(game->player->pos_x >> 6) << 6 + TILE;
	}
	else
	{
		game->rays->step_x = -TILE;
		game->rays->hit_x = floor(game->player->x / TILE) * TILE - 0.00001; //Rounded down float to double
	//	game->rays->hit_y = floor(game->player->pos_y >> 6) << 6 - 0.00001;
	}
	game->rays->hit_y = game->player->y + (game->player->x - game->rays->hit_x) * game->rays->tan;
	if (game->rays->ang == WEST || game->rays->ang == EAST) // LOOK STRAIGHT RIGHT OR LEFT
		game->rays->step_y = 0;								  // y gap = 0
	else
		game->rays->step_y = TILE * (game->rays->tan * -1);
	if (game->rays->ang >= NORTH && game->rays->ang <= SOUTH)
		game->rays->step_y *= -1;
	digital_differential_analyzer(game);
	return (sqrt(square((game->player->x - game->rays->hit_x))
		+ square((game->player->y - game->rays->hit_y))));
}

double	horizontal_raycasting(t_game *game)
{
	game->rays->tan = tan(degrees_to_radians(game->rays->ang));
	if (game->rays->ang > EAST && game->rays->ang < WEST) // LOOKING UP
	{
		game->rays->step_y = -TILE;
		game->rays->hit_y = floor(game->player->y / TILE) * TILE - 0.00001; //Rounded down float to double
	//	game->rays->hit_y = floor(game->player->pos_y >> 6) << 6 - 0.00001;
	}
	else
	{
		game->rays->step_y = TILE;
		game->rays->hit_y = floor(game->player->y / TILE) * TILE + TILE; //Rounded down float to double
	//	game->rays->hit_y = floor(game->player->pos_y >> 6) << 6 + TILE;
	}
	game->rays->hit_x = game->player->x + (game->player->y - game->rays->hit_y) / game->rays->tan;
	if (game->rays->ang == NORTH || game->rays->ang == SOUTH) // LOOK STRAIGHT UP OR DOWN
		game->rays->step_x = 0;								  // x gap = 0
	else
		game->rays->step_x = TILE / game->rays->tan;
	if (game->rays->ang > WEST)
		game->rays->step_x *= -1;
	digital_differential_analyzer(game);
	return (sqrt(square((game->player->x - game->rays->hit_x))
		+ square((game->player->y - game->rays->hit_y))));
}

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
	game->rays->dist *= cos(degrees_to_radians(game->player->orientation - game->rays->ang));
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

void	move_if_allowed(t_game *game)
{
	int	new_map_x;
	int	new_map_y;

	new_map_x = game->player->next_x / (int)TILE;
	new_map_y = game->player->next_y / (int)TILE;
	if (game->map[new_map_y][new_map_x] != WALL)
	{
		game->player->x = game->player->next_x;
		game->player->y = game->player->next_y;
	}
}

void	player_move(t_game *game)
{
	if (game->keys->movefor)
	{
		game->player->next_x = game->player->x + cos(degrees_to_radians(game->player->orientation)) * MOVESPEED;
		game->player->next_y = game->player->y - sin(degrees_to_radians(game->player->orientation)) * MOVESPEED;
	}
	else if (game->keys->moveback)
	{
		game->player->next_x = game->player->x - cos(degrees_to_radians(game->player->orientation)) * MOVESPEED;
		game->player->next_y = game->player->y + sin(degrees_to_radians(game->player->orientation)) * MOVESPEED;
	}
	else if (game->keys->moveright)
	{
		game->player->next_x = game->player->x + cos(degrees_to_radians(game->player->orientation + 90)) * MOVESPEED;
		game->player->next_y = game->player->y - sin(degrees_to_radians(game->player->orientation + 90)) * MOVESPEED;
	}
	else if (game->keys->moveleft)
	{
		game->player->next_x = game->player->x - cos(degrees_to_radians(game->player->orientation + 90)) * MOVESPEED;
		game->player->next_y = game->player->y + sin(degrees_to_radians(game->player->orientation + 90)) * MOVESPEED;
	}
	else if (game->keys->turnright)
		game->player->orientation += ROTATION;
	else if (game->keys->turnleft)
		game->player->orientation -= ROTATION;
	move_if_allowed(game);
}

void	raycasting(t_game *game)
{
	double	h_res;
	double	v_res;

	player_move(game);
	game->column = 0;
	game->rays->ang = game->player->orientation + FOV / 2;
	while (game->column < WIN_W)
	{
		game->flag_hori = 0;
//		game->rays->ang = fmod(game->rays->ang, 360.0); idea for the whiles (it
//		does not work :D)
		while (game->rays->ang >= 360)
			game->rays->ang -= 360;
		while (game->rays->ang < 0)
			game->rays->ang += 360;
		h_res = horizontal_raycasting(game);
		game->rays->h_hit_x = game->rays->hit_x;
		v_res = vertical_raycasting(game);
		game->rays->v_hit_y = game->rays->hit_y;
		if (h_res < v_res)
		{
			game->flag_hori = 1;
			game->rays->dist = h_res;
		}
		else
			game->rays->dist = v_res;
		draw(game);
		game->rays->ang -= FOV / (double)WIN_W;
		game->column++;
	}
}
