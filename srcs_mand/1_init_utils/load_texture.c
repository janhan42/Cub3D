/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:51:36 by janhan            #+#    #+#             */
/*   Updated: 2024/06/17 13:00:58 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

static void	load_wall_texture(t_game *game, t_img *wall)
{
	wall[EAST] = make_png_img_nomalloc(game, game->parse.tex[0].tex_path);
	wall[NORTH] = make_png_img_nomalloc(game, game->parse.tex[1].tex_path);
	wall[WEST] = make_png_img_nomalloc(game, game->parse.tex[2].tex_path);
	wall[SOUTH] = make_png_img_nomalloc(game, game->parse.tex[3].tex_path);
}

void	load_texture(t_game *game)
{
	t_img	*wall;

	wall = ft_calloc(4, sizeof(t_img));
	load_wall_texture(game, wall);
	game->texture = wall;
}
