/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:46:17 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:49:55 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

int	parse_color2(int *cf, char **color_malloc)
{
	int	i;
	int	x;
	int	color;

	i = 0;
	while (i < 3)
	{
		if (color_malloc[i] == NULL)
			return (FAILURE);
		*cf *= 256;
		x = 0;
		color = 0;
		while (color_malloc[i][x] != '\0' && color_malloc[i][x] != '\n')
		{
			if (ft_isdigit(color_malloc[i][x] == FALSE))
				return (FAILURE);
			color = color * 10 + color_malloc[i][x] - '0';
			x++;
		}
		if (255 < color || color < 0)
			return (FAILURE);
		*cf += color;
		i++;
	}
	return (SUCCESS);
}

int	parse_color(int *cf, char *line)
{
	char	**color_malloc;

	*cf = 0;
	while (is_upper(*line) == TRUE)
		line++;
	while (is_space(*line) == TRUE)
		line++;
	color_malloc = ft_split(line, ',');
	if (color_malloc == NULL || color_malloc[3] != NULL)
		return (FAILURE);
	if (parse_color2(cf, color_malloc) == FAILURE)
		return (FAILURE);
	free_array_memory((void **)color_malloc, 3);
	return (SUCCESS);
}

char	*update_map(char *s1, char *s2)
{
	char	*temp;
	char	*result;

	if (s1 == NULL)
		s1 = ft_strdup("");
	temp = ft_strjoin(s1, "\n");
	result = ft_strjoin(temp, s2);
	free_memory(s1);
	free_memory(temp);
	return (result);
}

int	parse_map(t_parse *parse, char *temp_map)
{
	int	row;
	int	col;

	parse->map = ft_split(temp_map, '\n');
	if (parse->map == NULL)
		return (free_memory_return(temp_map, FAILURE));
	row = 0;
	col = 0;
	while (parse->map[row] != NULL)
	{
		if ((int)ft_strlen(parse->map[row]) > col)
			col = ft_strlen(parse->map[row]);
		row++;
	}
	parse->row = row;
	parse->col = col;
	return (free_memory_return(temp_map, SUCCESS));
}

char	*parse_path_malloc(char *line)
{
	char	*temp;
	int		i;

	i = 0;
	while (line[i])
		i++;
	line[i - 1] = 0;
	while (is_upper(*line) == TRUE)
		line++;
	while (is_space(*line) == TRUE)
		line++;
	temp = ft_strdup(line);
	if (temp == NULL)
		return (NULL);
	return (temp);
}
