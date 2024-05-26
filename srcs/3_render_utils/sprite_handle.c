/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:21:37 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 07:15:49 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

// TODO: 이미지 스케일링 함수인데 전달 방식 및 처리 방식의 개편이 필요
/**
 * @brief
 *
 * @param src 변환전 오리지널 이미지 구조체.
 * @param dst 스케일링후 이미지를 넣을 구조체.
 * @param scale_factor 스케일
 */
void	scale_texture(t_img *src, t_img *dst, float scale_factor)
{
	t_scale	info;

	info.sacle = 1.0 / scale_factor;
	info.new_y = 0;
	while (info.new_y < dst->height)
	{
		info.new_x = 0;
		while (info.new_x < dst->width)
		{
			info.x = (int)(info.new_x * info.sacle);
			info.y = (int)(info.new_y * info.sacle);
			if (info.x >= src->width || info.y >= src->height)
				continue ;
			info.color = *(int *)(src->addr + (info.y * src->line_length
						+ info.x * (src->bit_per_pixel / 8)));
			*(int *)(dst->addr + (info.new_y * dst->line_length + info.new_x
						* (dst->bit_per_pixel / 8))) = info.color;
			info.new_x++;
		}
		info.new_y++;
	}
}

int	weapon_sprite_handle(t_game *game)
{
	t_img	dst_img;
	float	scale_factor;
	int		weapon_pos_x;
	int		weapon_pos_y;

	scale_factor = 0.5;
	if (game->player->shot == FALSE)
	{
		dst_img.width = (int)(game->player->shotgun[0]->width * scale_factor);
		dst_img.height = (int)(game->player->shotgun[0]->height * scale_factor);
		dst_img.img = mlx_new_image(game->mlx, dst_img.width, dst_img.height);
		dst_img.addr = mlx_get_data_addr(dst_img.img,
				&dst_img.bit_per_pixel, &dst_img.line_length, &dst_img.endian);
		weapon_pos_x = WINDOW_W / 2 - (dst_img.width / 2);
		weapon_pos_y = WINDOW_H - dst_img.height;
		scale_texture(game->player->shotgun[0], &dst_img, scale_factor);
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			dst_img.img,
			weapon_pos_x, weapon_pos_y);
		return (0);
	}
	if (game->player->shot == TRUE)
	{
		if (game->player->shot_frame < 3 && game->player->shot_time >= 100)
		{
			game->player->shot_frame++;
			game->player->shot_time = 0;
		}
		else if (game->player->shot_time >= 300)
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
		weapon_pos_x = WINDOW_W / 2 - (dst_img.width / 2);
		weapon_pos_y = WINDOW_H - dst_img.height;
		scale_texture(game->player->shotgun[game->player->shot_frame], &dst_img,  scale_factor);
	}
	print_img_info(dst_img.img, "shotgun");
	mlx_put_image_to_window(game->mlx, game->mlx_win, dst_img.img, weapon_pos_x, weapon_pos_y);
	return (0);
}

