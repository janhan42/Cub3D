/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:25:32 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/16 01:35:46 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

void	chekc(void)
{
	system("leaks cu3d");
}

double get_delta_time(struct timeval *last_time)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	double delta_time = (current_time.tv_sec - last_time->tv_sec) +
						(current_time.tv_usec - last_time->tv_usec) / 1000000.0;

	// 마지막 시간 갱신
	*last_time = current_time;

	return delta_time;
}

int	main(int ac, char **av)
{
	t_game	game;

	signal(SIGINT, kill_sound);
	init_map(&game, ac, av); // 구현중
	printf("--------------------raed_map OK--------------------\n");
	init_game(&game);
	printf("--------------------init_mlx OK--------------------\n");
	init_player(&game);
	printf("--------------------init_player OK--------------------\n");
	pthread_create(&game.sound_test, NULL, &sound_handle, &game); // 병렬 프로세스 TEST중
	pthread_create(&game.sound_test_theme, NULL, &sound_theme, &game); // 병렬 프로세스 TEST중

	printf("--------------------load_texture OK--------------------\n");

	print_game_info(&game);
	mlx_mouse_hook(game.mlx_win, mouse_handle, (void *)&game);
	mlx_hook(game.mlx_win, KEY_PRESS, 1L<<0, key_hook, &game);
	mlx_hook(game.mlx_win, KEY_RELEASE, 1L<<1, key_hook_release, &game);
	mlx_hook(game.mlx_win, WINDOW_CLOSE, 0, end_program, (void *)&game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	atexit(chekc);
	return (0);
}
