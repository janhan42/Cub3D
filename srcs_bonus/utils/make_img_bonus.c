/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:00:25 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/28 17:26:36 by sangshin         ###   ########.fr       */
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
