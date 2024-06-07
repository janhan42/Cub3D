/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:11:50 by sangshin          #+#    #+#             */
/*   Updated: 2024/06/07 14:40:23 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

char	*get_next_line(int fd)
{
	static char	*strings[OPEN_MAX + 1];
	char		*tmp;

	if (fd < 0 || fd > OPEN_MAX)
		return (0);
	if (reader(&strings[fd], fd) == 0)
	{
		free(strings[fd]);
		strings[fd] = 0;
		return (0);
	}
	tmp = cutter_cal(&strings[fd]);
	return (tmp);
}

char	*reader(char **string, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	long	read_size;
	int		i;

	while (1)
	{
		i = 0;
		while (i <= BUFFER_SIZE)
			buf[i++] = 0;
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size <= 0)
			break ;
		i = 0;
		while (buf[i] != 10 && buf[i])
			i++;
		*string = join(*string, buf);
		if (i < BUFFER_SIZE || *string == 0)
			break ;
	}
	if (read_size < 0)
		return (0);
	return (*string);
}

char	*join(char *string, char *buf)
{
	int		i;
	char	*tmp;

	i = 0;
	if (string == 0)
	{
		string = (char *)malloc(1);
		if (string == 0)
			return (0);
		string[0] = 0;
	}
	while (string[i])
		i++;
	tmp = (char *)malloc(i + BUFFER_SIZE + 1);
	i = -1;
	if (tmp != 0)
	{
		while (string[++i])
			tmp[i] = string[i];
		while (*buf)
			tmp[i++] = *buf++;
		tmp[i] = 0;
	}
	free(string);
	return (tmp);
}

char	*cutter_cal(char **string)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while ((*string)[i] != 10 && (*string)[i])
		i++;
	tmp = (char *)malloc(i + 1 + ((*string)[i] == 10));
	if (tmp == 0)
	{
		free(*string);
		*string = 0;
		return (0);
	}
	while (++j <= i)
		tmp[j] = (*string)[j];
	tmp[i + 0 + ((*string)[i] == 10)] = 0;
	if (j == 1 && (*string)[i] == 0)
	{
		free(tmp);
		tmp = 0;
	}
	*string = rose_knife(*string, i + 1);
	return (tmp);
}

char	*rose_knife(char *string, int i)
{
	int		len;
	int		j;
	char	*tmp;

	len = 0;
	j = -1;
	if (string == 0)
		return (0);
	if (string[i - 1] == 0)
	{
		free(string);
		string = 0;
		return (0);
	}
	while (string[i + len])
		len++;
	tmp = (char *)malloc(len + 1);
	if (tmp != 0)
		while (++j <= len)
			tmp[j] = string[i + j];
	free(string);
	return (tmp);
}
