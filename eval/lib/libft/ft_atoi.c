#include "libft.h"

int	ft_atoi(const char *str)
{
	int		cnt;
	int		minus;
	int		result;

	cnt = 0;
	minus = 1;
	result = 0;
	while (str[cnt] == ' ' || (str[cnt] >= '\t' && str[cnt] <= '\r'))
		cnt++;
	if (str[cnt] == '-' || str[cnt] == '+')
	{
		if (str[cnt] == '-')
			minus *= -1;
		cnt++;
	}
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		result = (result * 10) + (str[cnt] - '0');
		cnt++;
	}
	return (result * minus);
}
