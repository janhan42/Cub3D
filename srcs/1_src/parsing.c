/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:46:29 by janhan            #+#    #+#             */
/*   Updated: 2024/05/04 13:47:45 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_map_info(t_game *game, int i, int j)
{
	if (game->data->map[i][j] == 'N'
		|| game->data->map[i][j] == 'W'
		|| game->data->map[i][j] == 'S'
		|| game->data->map[i][j] == 'E')
	{
		game->data->dir.s = (4 * (game->data->map[i][j] == 'N') + 8
				* (game->data->map[i][j] == 'W') + 12
				* (game->data->map[i][j] == 'S')) * ANGLES;
		game->data->dir.angle = 90 * (game->data->map[i][j] == 'S') + 180
			* (game->data->map[i][j] == 'W') + 270
			* (game->data->map[i][j] == 'N');
		game->data->dir.x = j * 50 + 10;
		game->data->dir.y = i * 50 + 10;
		game->data->dir.px = game->data->dir.x;
		game->data->dir.py = game->data->dir.y;
		game->data->map[i][j] = '0';
		game->data->door.map[i][j] = '0';
	}
	if (game->data->map[i][j] == '*')
		init_map_info_sup(game, i, j);
}

void	check_map(t_game *game)
{
	int	i;
	int	j;

	game->data->enm_nb = 0;
	i = -1;
	while (game->data->map[++i])
	{
		j = -1;
		while (game->data->map[i][++j])
		{
			if (!ft_strchr(MAP_CHAR, game->data->map[i][j]))
				error_exit("invalid map character\n");
			if (game->data->map[i][j] != ' ' && game->data->map[i][j] != '1')
			{
				if (!i || !j || j + 1 == game->data->w_map[i]
					|| i + 1 == game->data->h_map
					|| game->data->map[i][j + 1] == ' '
					|| game->data->map[i][j - 1] == ' '
					|| game->data->map[i + 1][j] == ' '
					|| game->data->map[i - 1][j] == ' ')
					error_exit("invalid map\n");
				init_map_info(game, i, j);
			}
		}
	}
}

void	parse_map(t_game *game)
{
	int	i;

	i = 0;
	parse_map_sub(game);
	while (game->map)
	{
		if (game->map->content[0])
		{
			game->data->w_map[i] = ft_strlen(game->map->content);
			game->data->door.map[i] = ft_substr(game->map->content,
					0, game->data->w_map[i]);
			game->data->map[i] = ft_substr(game->map->content,
					0, game->data->w_map[i]);
			i++;
		}
		else
			error_exit("invalid map\n");
		game->map = game->map->next;
	}
	game->data->map[i] = NULL;
	game->data->door.map[i] = NULL;
}

void	parsing(t_game *game)
{
	game->data = (t_data *)malloc(sizeof(t_data));
	while (game->map)
	{
		if (game->map->content[0])
			break ;
		game->map = game->map->next;
	}
	parse_map(game);
	check_map(game);
}
