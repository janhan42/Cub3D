#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*result;

	result = malloc(num * size);
	if (!result)
		return (0);
	ft_bzero(result, num * size);
	return (result);
}
