#include "../../inc/cub3d.h"

double	degrees_to_radians(double value)
{
	return (value * PI / 180);
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
	while (game->map_pos_x > 0 && game->map_pos_x < MAP_W
		&& game->map_pos_y > 0 && game->map_pos_y < MAP_H
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
		game->rays->hit_x = floor(game->player->pos_x / TILE) * TILE + TILE; // Rounded up double to int
	//	game->rays->hit_x = floor(game->player->pos_x >> 6) << 6 + TILE;
	}
	else
	{
		game->rays->step_x = -TILE;
		game->rays->hit_x = floor(game->player->pos_x / TILE) * TILE - 0.00001; // Rounded up double to int
	//	game->rays->hit_y = floor(game->player->pos_y >> 6) << 6 - 0.00001;
	}
	game->rays->hit_y = game->player->pos_y + (game->player->pos_x - game->rays->hit_x) / game->rays->tan;
	if (game->rays->ang == WEST || game->rays->ang == EAST) // LOOK STRAIGHT RIGHT OR LEFT
		game->rays->step_y = 0;								  // y gap = 0
	else
		game->rays->step_y = TILE * -game->rays->tan;
	if (game->rays->ang >= NORTH && game->rays->ang <= SOUTH)
		game->rays->step_y = -game->rays->step_y;
	digital_differential_analyzer(game);
	return (sqrt(square((game->player->pos_x - game->rays->hit_x))
		+ square((game->player->pos_y - game->rays->hit_y))));
}

double	horizontal_raycasting(t_game *game)
{
	game->rays->tan = tan(degrees_to_radians(game->rays->ang));
	if (game->rays->ang > EAST && game->rays->ang < WEST) // LOOKING DOWN
	{
		game->rays->step_y = -TILE;
		game->rays->hit_y = floor(game->player->pos_y / TILE) * TILE - 0.00001; // Rounded up double to int
	//	game->rays->hit_y = floor(game->player->pos_y >> 6) << 6 - 0.00001;
	}
	else
	{
		game->rays->step_y = TILE;
		game->rays->hit_y = floor(game->player->pos_y / TILE) * TILE + TILE; // Rounded up double to int
	//	game->rays->hit_y = floor(game->player->pos_y >> 6) << 6 + TILE;
	}
	game->rays->hit_x = game->player->pos_x + (game->player->pos_y - game->rays->hit_y) / game->rays->tan;
	if (game->rays->ang == NORTH || game->rays->ang == SOUTH) // LOOK STRAIGHT UP OR DOWN
		game->rays->step_x = 0;								  // x gap = 0
	else
		game->rays->step_x = TILE / game->rays->tan;
	if (game->rays->step_x > WEST)
		game->rays->step_x = -game->rays->step_x;
	digital_differential_analyzer(game);
	return (sqrt(square((game->player->pos_x - game->rays->hit_x))
		+ square((game->player->pos_y - game->rays->hit_y))));
}

void	raycasting(t_game *game)
{
	double	h_res;
	double	v_res;

	game->column = 0;
	game->rays->ang = game->player->orientation + FOV / 2;
	while (game->column < WIN_W)
	{
		game->flag_hori = 0;
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
		//draw(game);
		game->rays->ang -= FOV / (double)WIN_W;
		game->column++;
	}
}

void	routine(t_game *game)
{
	//PUT BACKGROUND ?
	//RAYCASTING + DRAW WALLS

	raysting(game);

	//PUT IMAGE
}
