/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:42:08 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:55:30 by sangshin         ###   ########.fr       */
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

static void	update_object_sub(t_game *game, int i)
{
	if (game->objects[i]->state == OPEN
		&& game->objects[i]->frame < game->objects[i]->max_frame)
		game->objects[i]->frame++;
	if (game->objects[i]->state == CLOSE
		&& game->objects[i]->frame > 0)
		game->objects[i]->frame--;
	if (game->objects[i]->state == OPEN
		&& game->objects[i]->frame == game->objects[i]->max_frame)
	{
		if (game->objects[i]->type == HORIZONTAL_DOOR)
			game->map[(int)(game->objects[i]->object_y - 32) / 64]
			[(int)(game->objects[i]->object_x - 32) / 64] = 'O';
		else
			game->map[(int)(game->objects[i]->object_y - 32) / 64]
			[(int)(game->objects[i]->object_x - 32) / 64] = 'P';
	}
	else if (game->objects[i]->state == CLOSE && game->objects[i]->frame == 0)
	{
		if (game->objects[i]->type == HORIZONTAL_DOOR)
			game->map[(int)(game->objects[i]->object_y - 32) / 64]
			[(int)(game->objects[i]->object_x - 32) / 64] = 'H';
		else
			game->map[(int)(game->objects[i]->object_y - 32) / 64]
			[(int)(game->objects[i]->object_x - 32) / 64] = 'V';
	}
}

static void	update_object(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->object_count)
	{
		if (GREEN_LIGHT <= game->objects[i]->type
			&& game->objects[i]->type <= NOMAL_LIGHT)
		{
			if (game->objects[i]->frame < game->objects[i]->max_frame
				&& game->s_time >= 100)
				game->objects[i]->frame++;
			if (game->objects[i]->frame >= game->objects[i]->max_frame)
				game->objects[i]->frame = 0;
		}
		else
			update_object_sub(game, i);
		i++;
	}
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
	if (game->blood_flag == TRUE)
	{
		mlx_put_image_to_window(game->mlx,
			game->mlx_win, game->blood->img, 0, 0);
		game->blood_flag = FALSE;
	}
	mlx_destroy_image(game->mlx, game->minimap_img->img);
	free(game->minimap_img);
}

int	update(t_game *game)
{
	game->s_time++;
	if (game->player->shot == TRUE)
		game->player->shot_time++;
	if (game->mode == GAME)
		game_mouse_update(game);
	if (game->s_time >= 100)
	{
		if (game->mode == GAME)
		{
			player_movement(game);
			update_object(game);
			render_game(game);
		}
		if (game->mode == INTRO)
			render_intro(game);
		game->s_time = 0;
	}
	return (0);
}
