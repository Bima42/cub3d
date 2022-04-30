#include "../../inc/cub3d.h"

int	control_axis_x(char **map, int y, int max_y)
{
	int	x;

	x = 0;
	if (y == max_y)
		return (1); //gg
	if (map[y][x] != '\0')
	{
		skip_white_space(map[y], &x);
		while (map[y][x] == WALL && map[y][x] != '\0')
		{
			while (map[y][x] != '\0' && !is_w_space(map[y][x]))
				x++;
			if (map[y][x - 1] != WALL)
				return (0); // error
			skip_white_space(map[y], &x);
		}
		if (map[y][x] == '\0')
			return (control_axis_x(map, y + 1, max_y));
		else
			return (0); //error
	}
	return (0); //error
}

void	get_max(char **map, int *max_y, int *max_x)
{
	int	i;
	int	greater_value;

	i = 0;
	greater_value = 0;
	while (map[*max_y])
		*max_y += 1;
	while (i != *max_y)
	{
		while (map[i][*max_x])
			*max_x += 1;
		if (*max_x > greater_value)
			greater_value = *max_x;
		i++;
		*max_x = 0;
	}
	*max_x = greater_value;
}

int	check_map(char **map)
{
	int	max_y;
	int	max_x;

	max_y = 0;
	max_x = 0;
	get_max(map, &max_y, &max_x);
	if (!control_axis_x(map, 0, max_y))
	{
		printf("Map error !\n"); // remove and add better error message later
		return (0);
	}
	printf("map is ok !\n");
	return (1);
}
