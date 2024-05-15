#include "libft.h"

int	ft_isalnum(int character)
{
	if ((character >= 'A' && character <= 'Z') \
		|| (character >= 'a' && character <= 'z') \
		|| (character >= '0' && character <= '9'))
		return (1);
	return (0);
}
