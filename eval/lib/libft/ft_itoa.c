#include "libft.h"

static char	*ft_putnum(unsigned int num, size_t *sz)
{
	char	*rst;

	rst = (char *)malloc(sizeof(char) * (*sz + 1));
	if (!rst)
		return (0);
	rst[*sz] = '\0';
	while (num)
	{
		rst[*sz - 1] = num % 10 + '0';
		num /= 10;
		(*sz)--;
	}
	return (rst);
}

size_t	ter_func(int problem, int true, int false)
{
	if (problem == 1)
		return (true);
	return (false);
}

char	*ft_itoa(int n)
{
	size_t			size;
	char			*result;
	unsigned int	nb;

	size = ter_func(n > 0, 0, 1);
	nb = (unsigned int)ter_func(n > 0, n, -n);
	while (n)
	{
		n /= 10;
		size++;
	}
	result = ft_putnum(nb, &size);
	if (size == 1 && result[1] == '\0')
		result[0] = '0';
	else if (size == 1 && result[1] != '\0')
		result[0] = '-';
	return (result);
}
