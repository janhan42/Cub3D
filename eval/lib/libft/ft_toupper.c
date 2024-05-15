#include "libft.h"

int	ft_toupper(int character)
{
	if (character >= 'a' && character <= 'z')
		character -= ('a' - 'A');
	return (character);
}
