#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	src_len;

	if (!dst || !src)
		return (0);
	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	if (len != 0)
	{
		while (i < src_len && i < len - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}
