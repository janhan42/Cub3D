/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:51:34 by sangshin          #+#    #+#             */
/*   Updated: 2024/06/06 07:01:29 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

size_t	ft_maplcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < dstsize)
	{
		dst[i] = ' ';
		i++;
	}
	return (src_len);
}

static void	copy_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->parse.row)
	{
		ft_maplcpy(game->map[i], game->parse.map[i], game->parse.col);
		i++;
	}
}

static void	setting_line(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->parse.row)
	{
		x = 0;
		while (x < game->parse.col)
		{
			game->map[y][x] = ' ';
			x++;
		}
		y++;
	}
	copy_map(game);
}

static void	setting_map(t_game *game)
{
	int	i;

	game->map = (char **)ft_calloc(game->parse.row, sizeof(char *));
	if (game->map == NULL)
		error_exit("game->map malloc failed");
	i = 0;
	while (i < game->parse.row)
	{
		game->map[i] = (char *)ft_calloc(game->parse.col + 1, sizeof(char));
		if (game->map[i] == NULL)
		{
			while (i <= 0)
			{
				free(game->map[i]);
				i--;
			}
			free(game->map);
			error_exit("game->map[i] malloc failed");
		}
		i++;
	}
	setting_line(game);
}

void	init_map(t_game *game)
{
	setting_map(game);
	game->map_len_w = game->parse.col;
	game->map_len_h = game->parse.row;
	game->map_width = game->parse.col * PIXEL;
	game->map_height = game->parse.row * PIXEL;
	game->ceiling_color = game->parse.ceiling_color;
	game->floor_color = game->parse.floor_color;
}
