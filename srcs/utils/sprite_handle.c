/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:21:37 by janhan            #+#    #+#             */
/*   Updated: 2024/05/15 15:19:22 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

// TODO: 이미지 스케일링 함수인데 전달 방식 및 처리 방식의 개편이 필요
/**
 * @brief
 *
 * @param src 변환전 오리지널 이미지 구조체.
 * @param dst 스케일링후 이미지를 넣을 구조체.
 * @param scale_factor 스케일링 값.
 */
void scale_texture(t_img *src, t_img *dst, float scale_factor)
{
	int x, y;
	int new_x, new_y;
	int color;
	float inv_scale = 1.0 / scale_factor;

	for (new_y = 0; new_y < dst->height; new_y++) {
		for (new_x = 0; new_x < dst->width; new_x++) {
			x = (int)(new_x * inv_scale);
			y = (int)(new_y * inv_scale);
			if (x >= src->width || y >= src->height)
				continue;
			color = *(int *)(src->addr + (y * src->line_length + x * (src->bit_per_pixel / 8)));
			*(int *)(dst->addr + (new_y * dst->line_length + new_x * (dst->bit_per_pixel / 8))) = color;
		}
	}
}

int	weapon_sprite_handle(t_game *game)
{
	float scale_factor = 0.5;
	t_img dst_img;

	if (game->player->shot == FALSE)
	{
		dst_img.width = (int)(game->player->shotgun[0]->width * scale_factor);
		dst_img.height = (int)(game->player->shotgun[0]->height * scale_factor);
		dst_img.img = mlx_new_image(game->mlx, dst_img.width, dst_img.height);
		dst_img.addr = mlx_get_data_addr(dst_img.img, &dst_img.bit_per_pixel, &dst_img.line_length, &dst_img.endian);
		scale_texture(game->player->shotgun[0], &dst_img,  scale_factor);
		mlx_put_image_to_window(game->mlx, game->mlx_win, dst_img.img, WINDOW_W / 2 - (dst_img.width / 2), WINDOW_H - dst_img.height);
		return (0);
	}
	if (game->player->shot == TRUE)
	{
		if (game->player->shot_frame < 3 && game->player->shot_time >= 100)
		{
			game->player->shot_frame++;
			game->player->shot_time = 0;
		}
		else if (game->player->shot_time >= 100)
		{
			game->player->shot_frame++;
			game->player->shot_time = 0;
		}
		if (game->player->shot_frame == 5)
		{
			game->player->shot_frame = 0;
			game->player->shot = FALSE;
		}
		dst_img.width = (int)(game->player->shotgun[game->player->shot_frame]->width * scale_factor);
		dst_img.height = (int)(game->player->shotgun[game->player->shot_frame]->height * scale_factor);
		dst_img.img = mlx_new_image(game->mlx, dst_img.width, dst_img.height);
		dst_img.addr = mlx_get_data_addr(dst_img.img, &dst_img.bit_per_pixel, &dst_img.line_length, &dst_img.endian);
		scale_texture(game->player->shotgun[game->player->shot_frame], &dst_img,  scale_factor);
	}
	print_img_info(dst_img.img, "shotgun");
	mlx_put_image_to_window(game->mlx, game->mlx_win, dst_img.img, WINDOW_W / 2 - (dst_img.width / 2), WINDOW_H - dst_img.height);
	return (0);
}

