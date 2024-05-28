/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:25:32 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/28 17:28:32 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/header_bonus.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

// TODO: // 코드 정리, 구조체 정리, 로직 한번더 처리 및 생각
// 순서 init -> update -> key hook flag
// -> 정보 업데이트(플레이어 포지션에 따른 반응)-> 업데이트된 정보를 가지고 렌더 -> 화면에 띄우기
// TODO: 05m 26d minimap size와
// 미니맵 플레이어 사이즈 가변형 조절값이 필요함
// mapfile에서 받아온 텍스쳐 경로로 init하는거 처리 해야함
int	main(int ac, char **av)
{
	t_game	game;

	signal(SIGINT, kill_sound);
	init(&game, ac, av);
	pthread_create(&game.sound_test, NULL, &sound_handle, &game);
	pthread_create(&game.sound_test_theme, NULL, &sound_theme, &game);
	print_game_info(&game);
	mlx_mouse_hook(game.mlx_win, mouse_handle, (void *)&game);
	mlx_hook(game.mlx_win, KEY_PRESS, 1L << 0, key_hook, &game);
	mlx_hook(game.mlx_win, KEY_RELEASE, 1L << 1, key_hook_release, &game);
	mlx_hook(game.mlx_win, WINDOW_CLOSE, 0, end_program, (void *)&game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	return (0);
}
