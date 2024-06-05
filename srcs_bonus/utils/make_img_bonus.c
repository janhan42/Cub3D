/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:00:25 by sangshin          #+#    #+#             */
/*   Updated: 2024/06/05 21:58:01 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

/**
 * @brief
 * mlx_new_image fail 처리가 되어있음 (exit)
 * @param game
 * @param width 새로 만들 이미지의 가로
 * @param height 새로 만들 이미지의 세로
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
