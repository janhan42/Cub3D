/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:51:36 by janhan            #+#    #+#             */
/*   Updated: 2024/06/07 12:27:41 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

static void	load_menu_texture_sub(t_game *game)
{
	game->start_h = make_image(game, 154, 75);
	game->start_h->img = mlx_xpm_file_to_image(game->mlx,
			"resources/textures/Start_h.xpm",
			&game->start_h->width, &game->start_h->height);
	game->start_h->addr = mlx_get_data_addr(game->start_h->img,
			&game->start_h->bit_per_pixel,
			&game->start_h->line_length, &game->start_h->endian);
	game->exit_game_n = make_image(game, 240, 83);
	game->exit_game_n->img = mlx_xpm_file_to_image(game->mlx,
			"resources/textures/Exit_game_n.xpm",
			&game->exit_game_n->width, &game->exit_game_n->height);
	game->exit_game_n->addr = mlx_get_data_addr(game->exit_game_n->img,
			&game->exit_game_n->bit_per_pixel,
			&game->exit_game_n->line_length, &game->exit_game_n->endian);
	game->exit_game_h = make_image(game, 269, 93);
	game->exit_game_h->img = mlx_xpm_file_to_image(game->mlx,
			"resources/textures/Exit_game_h.xpm",
			&game->exit_game_h->width, &game->exit_game_h->height);
	game->exit_game_h->addr = mlx_get_data_addr(game->exit_game_h->img,
			&game->exit_game_h->bit_per_pixel,
			&game->exit_game_h->line_length, &game->exit_game_h->endian);
}

static void	load_menu_texture(t_game *game)
{
	game->main_menu = make_image(game, 1920, 1080);
	game->main_menu->img = mlx_xpm_file_to_image(game->mlx,
			"resources/textures/klipartz.com.xpm",
			&game->main_menu->width, &game->main_menu->height);
	game->main_menu->addr = mlx_get_data_addr(game->main_menu->img,
			&game->main_menu->bit_per_pixel,
			&game->main_menu->line_length, &game->main_menu->endian);
	game->main_background = make_image(game, 1920, 1080);
	game->main_background->img = mlx_xpm_file_to_image(game->mlx,
			"resources/textures/main_background.xpm",
			&game->main_background->width, &game->main_background->height);
	game->main_background->addr = mlx_get_data_addr(game->main_background->img,
			&game->main_background->bit_per_pixel,
			&game->main_background->line_length,
			&game->main_background->endian);
	game->start_n = make_image(game, 145, 71);
	game->start_n->img = mlx_xpm_file_to_image(game->mlx,
			"resources/textures/Start_n.xpm",
			&game->start_n->width, &game->start_n->height);
	game->start_n->addr = mlx_get_data_addr(game->start_n->img,
			&game->start_n->bit_per_pixel,
			&game->start_n->line_length, &game->start_n->endian);
	load_menu_texture_sub(game);
}

static void	load_wall_texture(t_game *game, t_img *tmp)
{
	tmp[EAST].img = mlx_png_file_to_image(game->mlx,
			game->parse.tex[0].tex_path, &tmp[EAST].width, &tmp[EAST].height);
	tmp[EAST].addr = mlx_get_data_addr(tmp[EAST].img,
			&tmp[EAST].bit_per_pixel,
			&tmp[EAST].line_length, &tmp[EAST].endian);
	tmp[NORTH].img = mlx_png_file_to_image(game->mlx,
			game->parse.tex[1].tex_path, &tmp[NORTH].width, &tmp[NORTH].height);
	tmp[NORTH].addr = mlx_get_data_addr(tmp[NORTH].img,
			&tmp[NORTH].bit_per_pixel,
			&tmp[NORTH].line_length, &tmp[NORTH].endian);
	tmp[WEST].img = mlx_png_file_to_image(game->mlx,
			game->parse.tex[2].tex_path, &tmp[WEST].width, &tmp[WEST].height);
	tmp[WEST].addr = mlx_get_data_addr(tmp[WEST].img,
			&tmp[WEST].bit_per_pixel,
			&tmp[WEST].line_length, &tmp[WEST].endian);
	tmp[SOUTH].img = mlx_png_file_to_image(game->mlx,
			game->parse.tex[3].tex_path, &tmp[SOUTH].width, &tmp[SOUTH].height);
	tmp[SOUTH].addr = mlx_get_data_addr(tmp[SOUTH].img,
			&tmp[SOUTH].bit_per_pixel,
			&tmp[SOUTH].line_length, &tmp[SOUTH].endian);
}

void	load_texture(t_game *game)
{
	t_img	*tmp;

	tmp = ft_calloc(4, sizeof(t_img));
	load_wall_texture(game, tmp);
	load_menu_texture(game);
	game->texture = tmp;
}
