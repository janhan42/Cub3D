/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:42:08 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 23:40:06 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	game_mouse_update(t_game *game)
{
	t_vec2i	mouse_diff;

	mlx_mouse_get_pos(game->mlx_win, &game->mouse->x, &game->mouse->y);
	mouse_diff.x = game->mouse->prev_x - game->mouse->x;
	mouse_diff.y = game->mouse->prev_y - game->mouse->y;
	if (mouse_diff.x > 0)
		game->player->player_rad -= 0.003 * abs(mouse_diff.x);
	if (mouse_diff.x < 0)
		game->player->player_rad += 0.003 * abs(mouse_diff.x);
	if (mouse_diff.y > 0)
		game->player->player_fov_off_y += mouse_diff.y * 3;
	if (mouse_diff.y < 0)
		game->player->player_fov_off_y += mouse_diff.y * 3;
	game->mouse->prev_x = WINDOW_W / 2;
	game->mouse->prev_y = WINDOW_H / 2;
	if (game->player->player_rad > M_PI * 2)
		game->player->player_rad -= 2 * M_PI;
	else if (game->player->player_rad < 0)
		game->player->player_rad += 2 * M_PI;
	if (game->mouse->x > 0 && game->mouse->y > 0)
		mlx_mouse_move(game->mlx_win, WINDOW_W / 2, WINDOW_H / 2);
}

/**
 * @brief
 * game->mode = GAME
 * @param game
 */
void	render_game(t_game *game)
{
	render_3d(game);
	render_mini_map_center(game);
	if (game->full_map == TRUE)
		render_map_player(game->minimap_img, game);
	else
		if (game->full_map_x == 0)
			render_map_player_center(game->minimap_img, game);
	mlx_put_image_to_window(game->mlx,
		game->mlx_win, game->minimap_img->img, 0, 0);
	render_weapon(game);
}

int	update(t_game *game)
{
	game->s_time++;
	if (game->player->shot == TRUE)
		game->player->shot_time++;
	if (game->s_time >= 100)
	{
		mlx_destroy_image(game->mlx, game->render->img);
		free(game->render);
		game->render = make_image(game, WINDOW_W, WINDOW_H);
		if (game->mode == GAME)
		{
			game_mouse_update(game);
			player_movement(game);
			render_game(game);
			render_sprite_object(game);
		}
		if (game->mode == INTRO)
			render_intro(game);
		game->s_time = 0;
	}
	return (0);
}
