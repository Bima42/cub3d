# cub3d
- [1. Get Started](#get-started)
- [2. Resume](#resume)
- [3. Parsing](#parsing)
  - [3.1 Map file](#map-file)
  - [3.2 Map](#map)
  - [3.3 Map Checker](#map-checker)
- [4. Raycasting](#raycasting)
  - [4.1 Explanation](#explanation)
  - [4.2 Horizontal Check](#horizontal-check)
  - [4.3 Vertical Check](#vertical-check)
  - [4.5 Digital Differential Analyzer](#digital-differential-analyzer)
  - [4.4 Fisheye Effect](#fisheye-effect)
- [5. Sources](#sources)

# Get Started
- Implement raycasting in a simple video game

```
git clone git@github.com:Bima42/cub3d.git
```
```
make
```
```
./cub3d maps/map.cub
```

<p align="center">
  <img src="/assets/cub3d.gif">
</p>

- Use W, A, S, D key to move
- Use left and right arrow to rotate camera
- Esc quit the game

- [FIND MY GENERATOR HERE](https://github.com/Bima42/cub3d_map_generator)

# Resume
- First part was the parsing
- Then, we split works in two parts : initialisation part (graphics, mlx ...) and raycasting part

# Parsing
## Map file
- Extension file is .cub only
- Begin by texture path (N, S, E, W)
- Then some rgb data for ceiling and floor
- Empty lines can be found between those datas

## Map
- Must be surrounded by '1', filled by '0'
- Only one player spawn (N, S, E or W indicate player orientation)
- Q for exit map

## Map Checker

<p align="center">
  <img src="/assets/parsing_map.png">
</p>

For every rows and colums (x and y) :
- Start with skip white spaces
- Then we have to hit a wall
- We skip all char except wall (1) until white space or \0
- If the char in pos - 1 is not a wall, it's an error
- The fact is if we hit a wall we have to found another one, walls works by pair. If the second wall was not hit, row (or column) is false

_Example for the x axis_

```c
int	control_axis_x(char **map, int y, int max_y)
{
	int	x;

	x = 0;
	if (y == max_y)
		return (1);
	if (map[y][x] != '\0')
	{
		skip_white_space(map[y], &x);
		while (map[y][x] == WALL && map[y][x] != '\0')
		{
			while (map[y][x] != '\0' && !is_w_space(map[y][x]))
				x++;
			if (map[y][x - 1] != WALL)
				return (0);
			skip_white_space(map[y], &x);
		}
		if (map[y][x] == '\0')
			return (control_axis_x(map, y + 1, max_y));
		else
			return (0);
	}
	return (0);
}
```
- During this check, we extract the higher x and y to reformat_map, using white_spaces to reformat and put every lines at the same length.

- Last line is filled with \0.
	
# Raycasting
## Explanation
- Transforming a limited form of data into a three-dimensional projection with the help of tracing rays from the view point into the viewing volume. 
- Rays can be cast and traced in groups based on certain geometric constraints.
- A ray from the pixel through the camera is obtained and the intersection of all objects in the picture is computed.

<p align="center">
  <img src="/assets/raycasting.png">
</p>

- There some steps to cast rays:
  - 1 : Based on the viewing angle, subtract 30 degrees (half of the FOV).
  - 2 : Starting from column 0.
  - 3 : Cast a ray.
  - 4 : Trace the ray until it hits a wall.
  - 5 : Record the distance to the wall (the distance = length of the ray).
  - 6 : Add the angle increment so that the ray moves to the right
  - 7 : Repeat steps from step 3 with a column+1. We gonna cast one ray per unit width

- We have to create a maze world that has the following geometric constraints:
  - Walls are always at 90° angle with the floor.
  - Walls are made of cubes that have the same size.
  - Floor is always flat.

- Need to define some attributes :
  - Player/viewer’s height, player’s field of view (FOV), and player’s position.
  - Projection plane’s dimension.
  - Relationship between player and projection plane.
  - FOV of 60 is generally a good choice.
  - Player height reprensent half of window height.

```c
void	raycasting(t_game *game)
{
	game->column = 0;
	game->rays.ang = game->p.vis + FOV / 2;
	while (game->column < WIN_W)
	{
		check_rays_angle(game);
		horizontal_raycasting(game);
		vertical_raycasting(game);
		draw(game);
		game->rays.ang -= FOV / (double)WIN_W;
		game->column++;
	}
}
```
- WARNING : You want to protect the player to go outside the 360 degrees available for rotation. 
```c
void check_rays_angle(t_game *game)
{
	while (game->rays.ang >= 360)
		game->rays.ang -= 360;
	while (game->rays.ang < 0)
		game->rays.ang += 360;
}
```

- To ensure that each ray stops at the first wall touched, it is necessary to carry out a horizontal and vertical check

## Horizontal Check

<p align="center">
  <img src="/assets/horizontal_check.png">
</p>

```c
double	horizontal_raycasting(t_game *game)
{
	game->rays.tan = tan(deg_to_rad(game->rays.ang));
	if (game->rays.ang > EAST && game->rays.ang < WEST)
	{
		game->rays.step_y = -TILE;
		game->rays.hit_y = floor(game->p.y / TILE) * TILE - 0.00001;
	}
	else
	{
		game->rays.step_y = TILE;
		game->rays.hit_y = floor(game->p.y / TILE) * TILE + TILE;
	}
	game->rays.hit_x = game->p.x
		+ (game->p.y - game->rays.hit_y) / game->rays.tan;
	if (game->rays.ang == NORTH || game->rays.ang == SOUTH)
		game->rays.step_x = 0;
	else
		game->rays.step_x = TILE / game->rays.tan;
	if (game->rays.ang > WEST)
		game->rays.step_x *= -1;
	digital_differential_analyzer(game);
	return (sqrt(square((game->p.x - game->rays.hit_x))
			+ square((game->p.y - game->rays.hit_y))));
}
```

## Vertical Check

<p align="center">
  <img src="/assets/vertical_check.png">
</p>

```c
double	vertical_raycasting(t_game *game)
{
	game->rays.tan = tan(deg_to_rad(game->rays.ang));
	if (game->rays.ang < NORTH || game->rays.ang > SOUTH)
	{
		game->rays.step_x = TILE;
		game->rays.hit_x = floor(game->p.x / TILE) * TILE + TILE;
	}
	else
	{
		game->rays.step_x = -TILE;
		game->rays.hit_x = floor(game->p.x / TILE) * TILE - 0.00001;
	}
	game->rays.hit_y = game->p.y
		+ (game->p.x - game->rays.hit_x) * game->rays.tan;
	if (game->rays.ang == WEST || game->rays.ang == EAST)
		game->rays.step_y = 0;
	else
		game->rays.step_y = TILE * (game->rays.tan * -1);
	if (game->rays.ang >= NORTH && game->rays.ang <= SOUTH)
		game->rays.step_y *= -1;
	digital_differential_analyzer(game);
	return (sqrt(square((game->p.x - game->rays.hit_x))
			+ square((game->p.y - game->rays.hit_y))));
}
```
## Digital Differential Analyzer
- This algorithm is used to progress by step in each checker (vertical and horizontal)
- We have to move for 1 Tile width for horizontal checker, and 1 Tile height for vertical checker

```c
void	digital_differential_analyzer(t_game *game)
{
	game->map_pos_x = game->rays.hit_x / (int)TILE;
	game->map_pos_y = game->rays.hit_y / (int)TILE;
	while (game->map_pos_x > 0 && game->map_pos_x < game->map_w
		&& game->map_pos_y > 0 && game->map_pos_y < game->map_h
		&& game->map[game->map_pos_y][game->map_pos_x] != '1')
	{
		if (game->map[game->map_pos_y][game->map_pos_x] == 'Q')
		{
			game->flag_exit = 1;
			break ;
		}
		game->rays.hit_x += game->rays.step_x;
		game->rays.hit_y += game->rays.step_y;
		game->map_pos_x = game->rays.hit_x / (int)TILE;
		game->map_pos_y = game->rays.hit_y / (int)TILE;
	}
}
```
- When horizontal and vertical intersections are merged, you have to check the lowest distance between player and wall using Pythagore theorem.
- Now you know which side of the wall you have to drawn.

## Fisheye effect
- This way will show distortion called "fish-eye".
- To remove the viewing distortion : ```correct_dist = distorted_dist * cos(angle);```

# Sources
- https://permadi.com/1996/05/ray-casting-tutorial-3/#CREATING%20A%20WORLD
- https://guy-grave.developpez.com/tutoriels/jeux/doom-wolfenstein-raycasting/
