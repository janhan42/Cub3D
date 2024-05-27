#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	str_len;
	char	*result;

	i = 0;
	str_len = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!result)
		return (0);
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
