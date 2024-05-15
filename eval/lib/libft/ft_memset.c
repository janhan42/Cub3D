#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*pb;
	size_t			i;

	i = 0;
	pb = ptr;
	while (i < num)
	{
		pb[i] = value;
		i++;
	}
	return (pb);
}
