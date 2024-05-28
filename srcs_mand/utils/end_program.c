/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:31:30 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:49:51 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

int	end_program(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}
