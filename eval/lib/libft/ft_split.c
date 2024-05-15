#include "libft.h"

static size_t	ft_cntword(const char *str, char c)
{
	size_t	cnt;
	size_t	flag;
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	cnt = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] != c && flag == 0)
		{
			flag = 1;
			cnt++;
		}
		else if (str[i] == c)
			flag = 0;
		i++;
	}
	return (cnt);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*ft_strndup(const char *s, size_t num)
{
	size_t	i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (num + 1));
	if (!word)
		return (0);
	while (i < num)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free_str(char **s, int i)
{
	while (i--)
		free(s[i]);
	free(s);
}

char	**ft_split(char const *s, char c)
{
	t_split	p;

	p.cnt = ft_cntword(s, c);
	p.result = (char **)malloc(sizeof(char *) * (p.cnt + 1));
	if (!p.result)
		return (0);
	p.nb = -1;
	while (++p.nb < p.cnt)
	{
		while (*s && *s == c)
			s++;
		p.wordlen = ft_wordlen(s, c);
		p.result[p.nb] = ft_strndup(s, p.wordlen);
		if (!p.result[p.nb])
		{
			ft_free_str(p.result, p.nb - 1);
			return (0);
		}
		s += p.wordlen;
	}
	p.result[p.cnt] = 0;
	return (p.result);
}
