#include "cub3d.h"

int	is_wall(t_god *god, double x, double y)
{
	int	xX;
	int	yY;

	xX = (int)floor(x / TILE_SIZE);
	yY = (int)floor(y / TILE_SIZE);
	return (ft_strchr("0NSEW", god->map.map[yY][xX]) == NULL);
}

int	is_upper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (TRUE);
	return (FALSE);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (TRUE);
	return (FALSE);
}
