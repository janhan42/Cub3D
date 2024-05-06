/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:09 by janhan            #+#    #+#             */
/*   Updated: 2024/04/29 16:00:13 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdio.h>

int	input(int key, t_game *game)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(game->mlx, &mouse_x, &mouse_y);
	printf("key : %d\nmouse x : %d\nmouse y : %d\n", key, mouse_x, mouse_y);
	return (1);
}
