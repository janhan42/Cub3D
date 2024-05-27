#include "cub3d.h"

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

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
