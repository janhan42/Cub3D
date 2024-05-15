/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:51:34 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/16 03:35:04 by janhan           ###   ########.fr       */
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

	map = ft_calloc(sizeof(char *), 11);
	map[0] = "1111111111";
	map[1] = "1000000001";
	map[2] = "101000000D";
	map[3] = "11G0S00001";
	map[4] = "1000000001";
	map[5] = "1010101011";
	map[6] = "1000000001";
	map[7] = "1000000001";
	map[8] = "1000000001";
	map[9] = "1111111111";
	map[10] = 0;

	height = 10;
	width = 10;
	// 맵 읽는 함수 추가 하면 지울것

	game->map = map;
	game->map_len_w = width;
	game->map_len_h = height;
	game->map_height = height * PIXEL;
	game->map_width = width * PIXEL;
	// 맵을 끝까지 읽었을때의 object 의 개수를 셀것
	game->object_count = 1;
	// 천장 바닥 색 불러오는 함수 추가 필요
	game->ceiling_color = 0x000a6eff;
	game->floor_color = 0x000a6e0a;
}
