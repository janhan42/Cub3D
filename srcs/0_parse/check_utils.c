/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:25:53 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 23:34:07 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

/**
 * @brief
 * 텍스쳐 중복 파일 체크
 * @param game
 * @return int
 */
int	check_tex(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= T_WE)
	{
		j = i;
		while (++j <= T_EA)
		{
			if (ft_strncmp(game->parse.tex[i].tex_path,
					game->parse.tex[j].tex_path,
					ft_strlen(game->parse.tex[i].tex_path)) == 0)
				return (ERROR);
		}
	}
	return (SUCCESS);
}
