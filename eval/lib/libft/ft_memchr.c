#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t num)
{
	const unsigned char	*pb;
	size_t				i;

	pb = ptr;
	i = 0;
	while (i < num)
	{
		if (pb[i] == (unsigned char)c)
			return ((void *)(pb + i));
		i++;
	}
	return (0);
}
