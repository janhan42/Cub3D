/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:51:36 by janhan            #+#    #+#             */
/*   Updated: 2024/06/17 13:07:21 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

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
	game->texture = wall;
}
