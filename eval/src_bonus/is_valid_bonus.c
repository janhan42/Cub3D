#include "cub3d_bonus.h"

int	is_door(t_god *god, double x, double y)
{
	int	xX;
	int	yY;

	xX = (int)floor(x / TILE_SIZE);
	yY = (int)floor(y / TILE_SIZE);
	if (ft_strchr("3", god->map.map[yY][xX]) != NULL)
		return (CLOSE_DOOR);
	else if (ft_strchr("4", god->map.map[yY][xX]) != NULL)
		return (OPEN_DOOR);
	return (FALSE);
}

int	is_wall(t_god *god, double x, double y)
{
	int	xX;
	int	yY;

	xX = (int)floor(x / TILE_SIZE);
	yY = (int)floor(y / TILE_SIZE);
	return (ft_strchr("02345NSEWF", god->map.map[yY][xX]) == NULL);
}

int	is_sprite(t_god *god, double x, double y)
{
	int	xX;
	int	yY;

	xX = (int)floor(x / TILE_SIZE);
	yY = (int)floor(y / TILE_SIZE);
	return (ft_strchr("2F", god->map.map[yY][xX]) != NULL);
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
