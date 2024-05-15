#include "libft.h"

char	*ft_strchr(const char *str, int character)
{
	while (*str != character)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return ((char *)str);
}
