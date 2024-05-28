/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:25:32 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/28 17:42:36 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_mand/header_mand.h"

int	main(int ac, char **av)
{
	t_game	game;

	init(&game, ac, av);
	mlx_hook(game.mlx_win, KEY_PRESS, 1L << 0, key_hook, &game);
	mlx_hook(game.mlx_win, KEY_RELEASE, 1L << 1, key_hook_release, &game);
	mlx_hook(game.mlx_win, WINDOW_CLOSE, 0, end_program, (void *)&game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	return (0);
}
