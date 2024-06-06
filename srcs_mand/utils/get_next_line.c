/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:51:49 by janhan            #+#    #+#             */
/*   Updated: 2024/06/06 09:05:38 by janhan           ###   ########.fr       */
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
	while (str != NULL && *str != '\0') // 문자열이 널이 아니고
	{
		if (*str == '\n') // 만약에 개행이 있으면
			return (cnt); // 거기까지의 인덱스를 리턴
		str++;
		cnt++;
	}
	return (FAILURE);
}

static ssize_t	make_line(char **line, char **save, ssize_t index)
{
	char	*temp;
	char	*next_line;

	if (index >= 0) // 개행이 들어있는 라인이면
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
	while ((g->index == FAILURE && g->offset > 0)) // index가 failure 고 g->offset 이 0보다 클때 읽은 글자가 있을때
	{
		g->buf[g->offset] = '\0'; // 널가드
		if (*save == NULL) // save가 처음 읽어들인 부분이면
			g->temp = ft_strndup(g->buf, g->offset); // 그대로 복사
		else
			g->temp = ft_strjoin(*save, g->buf); // 아니면 join으로 이어붙이기
		str_free(*save); // 이전 라인프리
		*save = g->temp; // 새롭게 업데이트된 문자열
		g->index = find_newline(*save); // 개행까지의 인덱스 저장
		if (g->index == FAILURE) // 만약에 개행이 없으면 버퍼에 한번더 read
			g->offset = read(fd, g->buf, 20);
	}
}

int	get_next_line(int fd, char **line)
{
	t_gnl		g;
	static char	*save[10240];

	if (fd < 0 || fd > 10240 || line == NULL)
		return (FAILURE);
	g.buf = (char *)malloc(sizeof(char) * (21)); // 20글자씩 읽어드릴 버퍼
	if (g.buf == NULL)
		return (FAILURE);
	g.index = FAILURE;
	g.offset = read(fd, g.buf, 20); // 버퍼에 20글자 읽어들임.
	gnl_tool(&save[fd], &g, fd);
	str_free(g.buf);
	if (g.offset < 0)
		return (FAILURE);
	return (make_line(line, &save[fd], g.index));
}
