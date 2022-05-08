#include "../../inc/cub3d.h"

int	color_picker(unsigned char red, unsigned char green,
		unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}
