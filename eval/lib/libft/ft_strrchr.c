#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	slen;

	slen = ft_strlen(s);
	while (slen != 0 && s[slen] != c)
		slen--;
	if (s[slen] == c)
		return ((char *)(s + slen));
	return (0);
}
