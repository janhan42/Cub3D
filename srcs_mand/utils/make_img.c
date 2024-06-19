/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:00:25 by sangshin          #+#    #+#             */
/*   Updated: 2024/06/19 12:46:01 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

/**
 * @brief
 * allocate new img struct and make new img with width and height
 * @param game
 * @param width new img width
 * @param height new img height
 * @return t_img*
 */
t_img	*make_image(t_game *game, int width, int height)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	img->img = mlx_new_image(game->mlx, width, height);
	if (img->img == NULL)
		error_exit("make_image failed");
	img->addr = mlx_get_data_addr(img->img, &img->bit_per_pixel,
			&img->line_length, &img->endian);
	img->width = width;
	img->height = height;
	return (img);
}

t_img	*make_xpm_img(t_game *game, char *file_path)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	img->img = mlx_xpm_file_to_image(game->mlx, file_path,
			&img->width, &img->height);
	if (img->img == NULL)
		error_exit("make_image failed");
	img->addr = mlx_get_data_addr(img->img, &img->bit_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

t_img	make_png_img_nomalloc(t_game *game, char *file_path)
{
	t_img	img;

	img.img = mlx_png_file_to_image(game->mlx, file_path,
			&img.width, &img.height);
	if (img.img == NULL)
		error_exit("make_image failed");
	img.addr = mlx_get_data_addr(img.img, &img.bit_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}
