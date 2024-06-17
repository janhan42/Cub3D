/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:51:36 by janhan            #+#    #+#             */
/*   Updated: 2024/06/17 13:03:58 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	load_menu_texture(t_game *game)
{
	game->main_menu = make_xpm_img(game,
			"resources/textures/klipartz.com.xpm");
	game->main_background = make_xpm_img(game,
			"resources/textures/main_background.xpm");
	game->start_n = make_xpm_img(game,
			"resources/textures/Start_n.xpm");
	game->start_h = make_xpm_img(game,
			"resources/textures/Start_h.xpm");
	game->exit_game_n = make_xpm_img(game,
			"resources/textures/Exit_game_n.xpm");
	game->exit_game_h = make_xpm_img(game,
			"resources/textures/Exit_game_h.xpm");
}

static void	load_wall_texture(t_game *game, t_img *wall)
{
	wall[EAST] = make_png_img_nomalloc(game, game->parse.tex[T_EA].tex_path);
	wall[NORTH] = make_png_img_nomalloc(game, game->parse.tex[T_NO].tex_path);
	wall[WEST] = make_png_img_nomalloc(game, game->parse.tex[T_WE].tex_path);
	wall[SOUTH] = make_png_img_nomalloc(game, game->parse.tex[T_SO].tex_path);
}

void	load_texture(t_game *game)
{
	t_img	*wall;

	wall = ft_calloc(4, sizeof(t_img));
	load_wall_texture(game, wall);
	load_menu_texture(game);
	game->texture = wall;
	game->blood = make_xpm_img(game, "resources/textures/blood_screen.xpm");
}
