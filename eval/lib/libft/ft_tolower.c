#include "libft.h"

int	ft_tolower(int character)
{
	if (character >= 'A' && character <= 'Z')
		character += ('a' - 'A');
	return (character);
}
