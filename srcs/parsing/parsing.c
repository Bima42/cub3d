#include "../inc/cub3d.h"

int	is_w_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	skip_white_space(char *str, int *i)
{
	while (is_w_space(str[*i]))
		*i += 1;
}

int	first_wall_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	skip_white_space(line, &i);
	while (line[i] == WALL)
	{
		i++;
		skip_white_space(line, &i);
		// petit trick si le haut de la map ressemble a ca :
		// 1111111     1111 1111111 11111
		// 100000111111100111000001110001
		// 100000000000000000000000000001
		// 100000000000000000000000000001
	}
	if (line[i] == '\0')
		return (1);
	return (0);
	// Dans cette fonction je skip les w space et apres je veux que des 1. si
	// il y a autre chose c'est pas considerer comme un mur
}

int	game_infos(t_game *game, t_parse *control)
{
	char	*line;

	line = get_next_line(control->fd);
	while (!first_wall_line(line))
	{
		// recuperer les datas ici, pas oublier de sauter les lignes vides
		// Il faut penser aussi a verifier la validiter des infos
		// car la fonction first_wall_line() va laisser passer si le premier
		// mur est defect genre : 1111111121111 Dans ce cas elle dira que c'est
		// pas un mur. donc dans ce while il faut trim la ligne pour garder que
		// le path et s'assurer que c'est pas un mur rater
		line = get_next_line(control->fd); // le laisser en last, toujours prendre la ligne et refaire la boucle
	}
	if (!check_all_datas(game))
		return (0);	// free en partant !
	game->map[0] = line; // on stock la ligne qui a ete detectee si c'est le premiere wall
}


int	check_file_format(char *str, char *str2 int start)
{
	// cette fonction c'est un strcmp avec un start point
	int	i;

	i = 0;
	while (str[start])
	{
		if (str[start] != str2[i])
			return(str[start] - str2[i]);
		else
		{
			start++;
			i++;
		}
	}
	return (0);
}

int	file_format(char *path, t_parse *control)
{
	int	size;

	size = ft_strlen(path);
	if (check_file_format(path, ".cub", size - 4))
		return (0);
	else
	{
		control->fd = open(path, O_RDONLY);
		if (control->fd < 0)
			return (0);
	}
	return (1);
}

void	init_parse(t_parse *control)
{
	control->fd = 0;
	control->spawn = 0;
	control->wall_err = 0;
	control->path_err = 0;
	control->id_err = 0;
	control->rgb_err = 0;
}

int	parsing(char *path, t_game *game)
{
	t_parse	control;

	init_parse(&control);
	if (!file_format(path, &control))
		return (1);
	if (!game_infos(game, &control))
		return (1);
	if (!collect_map())
		return (1);
}
