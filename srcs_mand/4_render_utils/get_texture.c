/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:54:36 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 15:54:49 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_img	*get_texture(t_game *game, t_dest *dest)
{
	if (dest->wall_type == EAST)
		return (&game->texture[EAST]);
	if (dest->wall_type == NORTH)
		return (&game->texture[NORTH]);
	if (dest->wall_type == WEST)
		return (&game->texture[WEST]);
	if (dest->wall_type == SOUTH)
		return (&game->texture[SOUTH]);
	else
		return (&game->texture[DOOR]);
}
