/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:51:36 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 07:58:27 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void load_door_texture(t_game *game, t_img *tmp)
{
	tmp[DOOR].img = mlx_png_file_to_image(game->mlx, "resources/doors/door_close.png", &tmp[DOOR].width, &tmp[DOOR].height);
	tmp[DOOR].addr = mlx_get_data_addr(tmp[DOOR].img, &tmp[DOOR].bit_per_pixel, &tmp[DOOR].line_length, &tmp[DOOR].endian);
}

static void load_wall_texture(t_game *game, t_img *tmp)
{
	tmp[EAST].img = mlx_png_file_to_image(game->mlx, "resources/textures/1.png", &tmp[EAST].width, &tmp[EAST].height);
	tmp[EAST].addr = mlx_get_data_addr(tmp[EAST].img, &tmp[EAST].bit_per_pixel, &tmp[EAST].line_length, &tmp[EAST].endian);
	tmp[NORTH].img = mlx_png_file_to_image(game->mlx, "resources/textures/2.png", &tmp[NORTH].width, &tmp[NORTH].height);
	tmp[NORTH].addr = mlx_get_data_addr(tmp[NORTH].img, &tmp[NORTH].bit_per_pixel, &tmp[NORTH].line_length, &tmp[NORTH].endian);
	tmp[WEST].img = mlx_png_file_to_image(game->mlx, "resources/textures/3.png", &tmp[WEST].width, &tmp[WEST].height);
	tmp[WEST].addr = mlx_get_data_addr(tmp[WEST].img, &tmp[WEST].bit_per_pixel, &tmp[WEST].line_length, &tmp[WEST].endian);
	tmp[SOUTH].img = mlx_png_file_to_image(game->mlx, "resources/textures/5.png", &tmp[SOUTH].width, &tmp[SOUTH].height);
	tmp[SOUTH].addr = mlx_get_data_addr(tmp[SOUTH].img, &tmp[SOUTH].bit_per_pixel, &tmp[SOUTH].line_length, &tmp[SOUTH].endian);
}

void	load_texture(t_game *game)
{
	t_img	*tmp;

	tmp = ft_calloc(5, sizeof(t_img));
	load_wall_texture(game, tmp);
	load_door_texture(game, tmp);
	game->texture = tmp;
	printf("--------------------load_texture OK--------------------\n");
}
