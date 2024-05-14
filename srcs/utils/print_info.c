/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:52:03 by janhan            #+#    #+#             */
/*   Updated: 2024/05/14 12:40:26 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

/**
 * @brief
 * game->ray_info->ray_result를 출력하는 함수
 * double *
 * @param ray_result game->ray_info->ray_result
 */
void	print_ray_result_info(double ray_result[4])
{
	printf("/*************************************************************/\n");
	printf("/*                ray_dest->dest[3] info                     */\n");
	printf("/*     game->ray_info->dest address : %-22p */\n", ray_result);
	printf("/*     double x                     : %-22f */\n", ray_result[0]);
	printf("/*     double y                     : %-22f */\n", ray_result[0]);
	printf("/*     double distance              : %-22f */\n", ray_result[0]);
	printf("/*************************************************************/\n");
}

/**
 * @brief
 * game->ray_info를 출력하는 함수
 * @param ray game->ray_info
 */
void	print_ray_info(t_ray_dest *ray)
{
	printf("/*************************************************************/\n");
	printf("/*                     ray_info info                         */\n");
	printf("/*     ray_info address    : %-31p */\n", ray);
	printf("/*     double rx                   : %-31f */\n", ray->rx);
	printf("/*     double ry                   : %-31f */\n", ray->ry);
	printf("/*     double hx                   : %-31f */\n", ray->hx);
	printf("/*     double hy                   : %-31f */\n", ray->hy);
	printf("/*     double vx                   : %-31f */\n", ray->vx);
	printf("/*     double vy                   : %-31f */\n", ray->vy);
	printf("/*     double xo                   : %-31f */\n", ray->xo);
	printf("/*     double yo                   : %-31f */\n", ray->yo);
	printf("/*     double distance_h           : %-31f */\n", ray->distance_h);
	printf("/*     double distance_v           : %-31f */\n", ray->distance_v);
	printf("/*     double a_tan                : %-31f */\n", ray->a_tan);
	printf("/*     double n_tan                : %-31f */\n", ray->n_tan);
	printf("/*     int map_x                   : %-31d */\n", ray->mx);
	printf("/*     int map_y                   : %-31d */\n", ray->my);
	printf("/*     int dof                     : %-31d */\n", ray->dof);
	printf("/*************************************************************/\n");
}

/**
 * @brief
 * game->mouse를 출력하는 함수
 * @param mouse game->mouse
 */
void	print_mouse_info(t_mouse *mouse)
{
	printf("/*************************************************************/\n");
	printf("/*                    game->mouse  OK                        */\n");
	printf("/*     game->mouse address : %-31p */\n", mouse);
	printf("/*     int mouse_x         : %-31d */\n", mouse->mouse_x);
	printf("/*     int mouse_y         : %-31d */\n", mouse->mouse_y);
	printf("/*     int prev_x          : %-31d */\n", mouse->prev_x);
	printf("/*     int prev_y          : %-31d */\n", mouse->prev_y);
	printf("/*************************************************************/\n");
}

/**
 * @brief
 * t_img 구조체를 출력하는 함수
 * @param img 출력할 구조체 포인터
 * @param name 출력할 이미지의 이름
 */
void	print_img_info(t_img *img, char *name)
{
	int border_len = 61;
	int name_len = ft_strlen(name);
	int padding = (border_len - 2 - name_len) / 2;
	int left_padding = padding + ((border_len - 4 - name_len) % 2);
	int right_padding = padding;

	printf("/%.*s/\n", border_len, "**************************************************************");
	printf("/*%*s%s%*s*/\n", left_padding, "", name, right_padding, "");
	printf("/*     t_img address       : %-31p */\n", img);
	printf("/*     void *img           : %-31p */\n", img->img);
	printf("/*     char *addr          : %-31p */\n", img->addr);
	printf("/*     int bit_per_pixel   : %-31d */\n", img->bit_per_pixel);
	printf("/*     int line_length     : %-31d */\n", img->line_length);
	printf("/*     int endian          : %-31d */\n", img->endian);
	printf("/*     int width           : %-31d */\n", img->width);
	printf("/*     int height          : %-31d */\n", img->height);
	printf("/%.*s/\n", border_len, "**************************************************************");
}

/**
 * @brief
 * game->player 구조체를 출력하는 함수
 * @param player game->player
 */
void	print_player_info(t_player *player)
{
	printf("/*************************************************************/\n");
	printf("/*                      PLAYER   INFO                        */\n");
	printf("/*     player address      : %-31p */\n", player);
	printf("/*     double player_x     : %-31f */\n", player->player_x);
	printf("/*     double player_y     : %-31f */\n", player->player_y);
	printf("/*     double player_rad   : %-31f */\n", player->player_rad);
	printf("/*     int    player_y_off : %-31d */\n", player->player_fov_off_y);
	printf("/*     int    shot         : %-31d */\n", player->shot);
	printf("/*     int    shot_sound   : %-31d */\n", player->shot_sound);
	printf("/*     int    shot_frame   : %-31d */\n", player->shot_frame);
	printf("/*     int    shot_time    : %-31d */\n", player->shot_time);
	printf("/*     int    move_w       : %-31d */\n", player->move_w);
	printf("/*     int    move_s       : %-31d */\n", player->move_s);
	printf("/*     int    move_a       : %-31d */\n", player->move_a);
	printf("/*     int    move_d       : %-31d */\n", player->move_d);
	printf("/*************************************************************/\n");
}
