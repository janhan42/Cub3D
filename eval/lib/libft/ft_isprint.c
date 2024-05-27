#include "libft.h"

int	ft_isprint(int character)
{
	if (character >= ' ' && character <= '~')
		return (1);
	return (0);
}
