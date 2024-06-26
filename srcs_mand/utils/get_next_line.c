/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:51:49 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:41:50 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

static char	*ft_strndup(const char *str, ssize_t offst)
{
	char	*result;
	ssize_t	cnt;

	cnt = 0;
	result = (char *)malloc(sizeof(char) * (offst + 1));
	if (!result)
		return (0);
	while (*str != '\0' && cnt < offst)
	{
		*result++ = *str++;
		cnt++;
	}
	*result = '\0';
	return (result - cnt);
}

static ssize_t	find_newline(char *str)
{
	ssize_t	cnt;

	cnt = 0;
	while (str != NULL && *str != '\0')
	{
		if (*str == '\n')
			return (cnt);
		str++;
		cnt++;
	}
	return (FAILURE);
}

static ssize_t	make_line(char **line, char **save, ssize_t index)
{
	char	*temp;
	char	*next_line;

	if (index >= 0)
	{
		*line = ft_strndup(*save, index);
		next_line = *save + index + 1;
		temp = ft_strndup(next_line, ft_strlen(next_line));
		str_free(*save);
		*save = temp;
		return (1);
	}
	if (*save == NULL)
		*line = ft_strndup("", 0);
	else
	{
		*line = *save;
		*save = NULL;
	}
	return (0);
}

void	gnl_tool(char **save, t_gnl *g, int fd)
{
	while (g->index == FAILURE && g->offset > 0)
	{
		g->buf[g->offset] = '\0';
		if (*save == NULL)
			g->temp = ft_strndup(g->buf, g->offset);
		else
			g->temp = ft_strjoin(*save, g->buf);
		str_free(*save);
		*save = g->temp;
		g->index = find_newline(*save);
		if (g->index == FAILURE)
			g->offset = read(fd, g->buf, 20);
	}
}

int	get_next_line(int fd, char **line)
{
	t_gnl		g;
	static char	*save[10240];

	if (fd < 0 || fd > 10240 || line == NULL)
		return (FAILURE);
	g.buf = (char *)malloc(sizeof(char) * (21));
	if (g.buf == NULL)
		return (FAILURE);
	g.index = FAILURE;
	g.offset = read(fd, g.buf, 20);
	gnl_tool(&save[fd], &g, fd);
	str_free(g.buf);
	if (g.offset < 0)
		return (FAILURE);
	return (make_line(line, &save[fd], g.index));
}
