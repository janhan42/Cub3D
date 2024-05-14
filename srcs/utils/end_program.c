/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:31:30 by janhan            #+#    #+#             */
/*   Updated: 2024/05/14 10:13:14 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	key_press(int key, t_game *game)
{
	printf("Key : %d\n", key);
	if (key == 53)
		end_program(game);
	return (0);
}

int	end_program(t_game *game)
{
	game->pthread_kill = TRUE;
	system("kill -9 $(ps | grep sound/ | grep -v grep | sed 's/^[ \\t]*//g' | cut -d ' ' -f 1)"); // sound 쓰레드 전체 종료
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}

void	kill_sound(int sig)
{
	sig++;
	system("kill -9 $(ps | grep sound/ | grep -v grep | sed 's/^[ \\t]*//g' | cut -d ' ' -f 1)"); // sound 쓰레드 전체 종료
	exit(0);
}
