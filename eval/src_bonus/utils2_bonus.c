#include "cub3d_bonus.h"

int	ternaries_func(int problem, int true, int false)
{
	if (problem == TRUE)
		return (true);
	return (false);
}

double	ternaries_func2(double problem, double true, double false)
{
	if (problem == TRUE)
		return (true);
	return (false);
}

void	make_even_value(int *num1, int *num2)
{
	if (*num1 % 2 != 0)
		*num1 += 1;
	if (*num2 % 2 != 0)
		*num2 += 1;
}

void	change_value(t_sprite *s1, t_sprite *s2)
{
	t_sprite	temp;

	temp.x = s1->x;
	temp.y = s1->y;
	temp.distance = s1->distance;
	temp.symbol = s1->symbol;
	s1->x = s2->x;
	s1->y = s2->y;
	s1->distance = s2->distance;
	s1->symbol = s2->symbol;
	s2->x = temp.x;
	s2->y = temp.y;
	s2->distance = temp.distance;
	s2->symbol = temp.symbol;
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
