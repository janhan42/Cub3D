/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:31:30 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:56:19 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	end_program(t_game *game)
{
	game->pthread_kill = TRUE;
	system("kill -9 $(ps | grep sound/ | grep -v\
	 grep | sed 's/^[ \\t]*//g' | cut -d ' ' -f 1)");
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}

void	kill_sound(int sig)
{
	sig++;
	(void)sig;
	system("kill -9 $(ps | grep sound/ | grep -v\
	 grep | sed 's/^[ \\t]*//g' | cut -d ' ' -f 1)");
	exit(0);
}
