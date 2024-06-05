/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:53:45 by janhan            #+#    #+#             */
/*   Updated: 2024/06/05 19:04:54 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	set_object_position_sub(t_object *object, char **map, int x, int y)
{
	if (map[y][x] == 'L')
	{
		object->type = NOMAL_LIGHT;
		object->max_frame = 1;
	}
	if (map[y][x] == 'H')
	{
		object->type = HORIZONTAL_DOOR;
		object->max_frame = 3;
	}
	if (map[y][x] == 'V')
	{
		object->type = VERTICAL_DOOR;
		object->max_frame = 3;
	}
}

static void	set_object_position(t_object *object, char **map, int x, int y)
{
	object->object_x = x * PIXEL + (int)(PIXEL / 2);
	object->object_y = y * PIXEL + (int)(PIXEL / 2);
	object->object_z = 0;
	if (map[y][x] == 'G')
	{
		object->type = GREEN_LIGHT;
		object->max_frame = 4;
	}
	if (map[y][x] == 'R')
	{
		object->type = RED_LIGHT;
		object->max_frame = 4;
	}
	set_object_position_sub(object, map, x, y);
	object->state = CLOSE;
	object->img_pos_x = 0;
	object->img_pos_y = 0;
	object->img_pos_z = 0;
	object->frame = 0;
}

static void	get_object_position(char **map, t_object **object)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'G'
				|| map[y][x] == 'R'
				|| map[y][x] == 'L'
				|| map[y][x] == 'H'
				|| map[y][x] == 'V')
			{
				set_object_position(object[i], map, x, y);
				i++;
			}
			x++;
		}
		y++;
	}
}

static void	load_object_textures(t_game *game)
{
	game->object_texture = (t_img ***)malloc(sizeof(t_img **) * 4);
	if (game->object_texture == NULL)
		error_exit("object_texture malloc failed");
	game->object_texture[GREEN_LIGHT] = (t_img **)malloc(sizeof(t_img *) * 4);
	init_multi_xpm_img(game, game->object_texture[GREEN_LIGHT],
		"resources/sprites/animated_sprites/green_light_low/", 4);
	game->object_texture[RED_LIGHT] = (t_img **)malloc(sizeof(t_img *) * 4);
	init_multi_xpm_img(game, game->object_texture[RED_LIGHT],
		"resources/sprites/animated_sprites/red_light_low/", 4);
	game->object_texture[NOMAL_LIGHT] = (t_img **)malloc(sizeof(t_img *));
	game->object_texture[NOMAL_LIGHT][0] = (t_img *)malloc(sizeof(t_img));
	game->object_texture[NOMAL_LIGHT][0]->img = mlx_xpm_file_to_image(game->mlx,
			"resources/sprites/static_sprites/candlebra.xpm",
			&game->object_texture[NOMAL_LIGHT][0]->width,
			&game->object_texture[NOMAL_LIGHT][0]->height);
	game->object_texture[NOMAL_LIGHT][0]->addr = mlx_get_data_addr(
			game->object_texture[NOMAL_LIGHT][0]->img,
			&game->object_texture[NOMAL_LIGHT][0]->bit_per_pixel,
			&game->object_texture[NOMAL_LIGHT][0]->line_length,
			&game->object_texture[NOMAL_LIGHT][0]->endian);
	game->object_texture[HORIZONTAL_DOOR]
		= (t_img **)malloc(sizeof(t_img *) * 4);
	init_multi_png_img(game,
		game->object_texture[HORIZONTAL_DOOR],
		"resources/doors/", 4);
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
		i++;
	}
	get_object_position(game->map, game->objects);
	load_object_textures(game);
}
