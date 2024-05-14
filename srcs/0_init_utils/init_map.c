/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:51:34 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/14 09:13:14 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

/**
 * @brief
 * 	맵 파싱 함수 TODO: 구현중
 * @param game
 * @param ac
 * @param av
 */
void	init_map(t_game *game, int ac, char **av)
{
	/* ac, av로 파싱하는 부분 여기 추가
	if (ac != 2)
		exit(0);
	*/
	(void)ac;
	(void)av;

	// 아래는 임시 코드
	char	**map;
	int		height;
	int		width;

	map = ft_calloc(sizeof(char *), 6);
	map[0] = "111111";
	map[1] = "100101";
	map[2] = "101001";
	map[3] = "1100S1";
	map[4] = "111111";
	map[5] = 0;

	height = 5;
	width = 6;
	// 맵 읽는 함수 추가 하면 지울것

	game->map = map;
	game->map_height = height * 64;
	game->map_width = width * 64;

	// 천장 바닥 색 불러오는 함수 추가 필요
	game->ceiling_color = 0x000a6eff;
	game->floor_color = 0x000a6e0a;
}
