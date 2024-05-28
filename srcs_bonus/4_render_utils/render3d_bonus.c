/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:34:45 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/28 17:24:43 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

/*
 * f_dest[0] = x좌표
 * f_dest[1] = y
 * f_dest[2] = distance
 * f_dest[3] = direction
*/
void	render_3d(t_game *game)
{
	t_dest	*f_dest;
	double	ray_direction;
	double	ray_destination;
	double	ca;
	int		t;

	t = 0;
	ray_destination = game->player->player_rad
		+ (0.000545415391 * WINDOW_W / 2);
	ray_direction = game->player->player_rad
		- (0.000545415391 * WINDOW_W / 2);
	while (ray_direction <= ray_destination)
	{
		f_dest = get_dest(game->player->player_x, game->player->player_y,
				ray_direction, game);
		ca = game->player->player_rad - ray_direction;
		f_dest->distance = f_dest->distance * cos(ca);
		render_texture(game, f_dest, t);
		free(f_dest);
		ray_direction += 0.000545415391;
		t++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render->img, 0, 0);
}

//void	render(t_game *game, double distance, int time, int side)
//{
//	t_img	*render;
//	t_2dot	dots;
//	double	line_h;
//	int		mid;
//	int		color;
//	int		i;

//	i = 0;
//	if (side == 0)
//		color = 0x00996666;
//	else if (side == 1)
//		color = 0x00ff6600;
//	else if (side == 2)
//		color = 0x00ff9933;
//	else
//		color = 0x00cc6600;
//	mid = 1080/2;
//	mid += game->player->player_fov_off_y;
//	line_h = (1080/(distance)) * 70;
//	render = game->render;
//	dots.start_x = time;
//	dots.start_y = mid;
//	dots.dest_x = time;
//	while (i < 1)
//	{
//		dots.dest_y = mid - line_h / 2;
//			dots.start_x += 1;
//			dots.dest_x += 1;
//		if (dots.dest_y < 0)
//			dots.dest_y = 0;
//		draw_line(render, dots, color);
//		dots.dest_y = mid + line_h/2;
//		if (dots.dest_y > WINDOW_H)
//			dots.dest_y = WINDOW_H;
//		draw_line(render, dots);
//		i++;
//	}
//}
