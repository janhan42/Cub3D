/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:53:45 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:23:28 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	set_object_position(t_object *object, char **map, int x, int y)
{
	object->object_x = x * PIXEL + (int)(PIXEL / 2);
	object->object_y = y * PIXEL + (int)(PIXEL / 2);
	object->object_z = 0;
	if (map[y][x] == 'G')
		object->type = GREEN_LIGHT;
	if (map[y][x] == 'R')
		object->type = RED_LIGHT;
	if (map[y][x] == 'L')
		object->type = NOMAL_LIGHT;
	object->img_pos_x = 0;
	object->img_pos_y = 0;
	object->img_pos_z = 0;
}

static void	get_object_position(char **map, t_object *object)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'G' || map[y][x] == 'R' || map[y][x] == 'L')
			{
				set_object_position(object, map, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_object(t_game *game)
{
	int	i;

	if (game->object_count == 0)
		return ;
	i = 0;
	game->objects
		= (t_object **)malloc(sizeof(t_object *) * game->object_count);
	if (game->objects == NULL)
		error_exit("init_object malloc failed");
	while (i < game->object_count)
	{
		game->objects[i] = (t_object *)malloc(sizeof(t_object));
		if (game->objects == NULL)
			error_exit("init_object malloc failed");
		get_object_position(game->map, game->objects[i]);
		i++;
	}
	game->object_texture = (t_img *)malloc(sizeof(t_img));
	game->object_texture->img = mlx_xpm_file_to_image(game->mlx,
			"resources/sprites/static_sprites/candlebra.xpm",
			&game->object_texture->width, &game->object_texture->height);
	game->object_texture->addr = mlx_get_data_addr(game->object_texture->img,
			&game->object_texture->bit_per_pixel,
			&game->object_texture->line_length, &game->object_texture->endian);
	print_object_info(game->objects[0]);
}
