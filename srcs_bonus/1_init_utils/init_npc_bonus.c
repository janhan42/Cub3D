/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_npc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 06:33:44 by janhan            #+#    #+#             */
/*   Updated: 2024/06/16 17:50:52 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	set_npc_position(t_npc *npc, char **map, int x, int y)
{
	npc->npc_x = x * PIXEL + (int)(PIXEL / 2);
	npc->npc_y = y * PIXEL + (int)(PIXEL / 2);
	npc->npc_z = 0;
	npc->state = IDLE;
	npc->frame = 0;
	npc->frame_max = 7;
	npc->frame_time = 0;
	npc->hp = 3;
	if (map[y][x] == 'T')
		npc->type = CACO_DEMON;
}

static void	get_npc_position(char **map, t_npc **npcs)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'T')
			{
				set_npc_position(npcs[i], map, x, y);
				i++;
			}
			x++;
		}
		y++;
	}
}

void	load_npc_texture(t_game *game)
{
	game->npc_texture = (t_img ****)malloc(sizeof(t_img ***));
	if (game->npc_texture == NULL)
		error_exit("game->npc_texture **** malloc failed");
	game->npc_texture[CACO_DEMON] = (t_img ***)malloc(sizeof(t_img **) * 5);
	game->npc_texture[CACO_DEMON][IDLE] = (t_img **)malloc(sizeof(t_img *) * 8);
	game->npc_texture[CACO_DEMON][WALK] = (t_img **)malloc(sizeof(t_img *) * 4);
	game->npc_texture[CACO_DEMON][ATTACK]
		= (t_img **)malloc(sizeof(t_img *) * 5);
	game->npc_texture[CACO_DEMON][PAIN] = (t_img **)malloc(sizeof(t_img *) * 2);
	game->npc_texture[CACO_DEMON][DEATH]
		= (t_img **)malloc(sizeof(t_img *) * 6);
	init_multi_png_img(game, game->npc_texture[CACO_DEMON][IDLE],
		"resources/sprites/npc/caco_demon/idle/", 8);
	init_multi_png_img(game, game->npc_texture[CACO_DEMON][WALK],
		"resources/sprites/npc/caco_demon/walk/", 4);
	init_multi_png_img(game, game->npc_texture[CACO_DEMON][ATTACK],
		"resources/sprites/npc/caco_demon/attack/", 5);
	init_multi_png_img(game, game->npc_texture[CACO_DEMON][PAIN],
		"resources/sprites/npc/caco_demon/pain/", 2);
	init_multi_png_img(game, game->npc_texture[CACO_DEMON][DEATH],
		"resources/sprites/npc/caco_demon/death/", 6);
}

void	init_npc(t_game *game)
{
	int	i;

	if (game->npc_count == 0)
		return ;
	i = 0;
	game->npcs = (t_npc **)malloc(sizeof(t_npc *) * game->npc_count);
	if (game->npcs == NULL)
		error_exit("init_npcs malloc failed");
	while (i < game->npc_count)
	{
		game->npcs[i] = (t_npc *)malloc(sizeof(t_npc));
		if (game->npcs[i] == NULL)
			error_exit("init_npcs[i] malloc failed");
		i++;
	}
	get_npc_position(game->map, game->npcs);
	load_npc_texture(game);
}
