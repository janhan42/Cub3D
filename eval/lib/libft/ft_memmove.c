#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	const unsigned char	*sp;
	unsigned char		*dp;
	size_t				i;

	i = -1;
	sp = src;
	dp = dst;
	if (!dst && !src)
		return (0);
	if (dst > src)
		while (++i < num)
			dp[num - 1 - i] = sp[num - 1 - i];
	else
	{
		while (i < num)
		{
			dp[i] = sp[i];
			i++;
		}
	}
	return (dst);
}
