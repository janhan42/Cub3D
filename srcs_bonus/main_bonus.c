/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:25:32 by sangshin          #+#    #+#             */
/*   Updated: 2024/06/06 15:42:10 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/header_bonus.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	signal(SIGINT, kill_sound);
	init(game, ac, av);
	pthread_create(&game->sound_test, NULL, &sound_handle, game);
	pthread_create(&game->sound_test_theme, NULL, &sound_theme, game);
	pthread_create(&game->npc_sound, NULL, &sound_npc, game);
	mlx_mouse_hook(game->mlx_win, mouse_handle, (void *)game);
	mlx_hook(game->mlx_win, KEY_PRESS, 1L << 0, key_hook, game);
	mlx_hook(game->mlx_win, KEY_RELEASE, 1L << 1, key_hook_release, game);
	mlx_hook(game->mlx_win, WINDOW_CLOSE, 0, end_program, (void *)game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	return (0);
}
