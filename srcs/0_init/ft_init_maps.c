/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:28:52 by janhan            #+#    #+#             */
/*   Updated: 2024/05/04 10:29:02 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_maps(char **av, t_game *game)
{
	char	*buff;
	int		fd;

	buff = NULL;
	fd = open(av[1], O_RDONLY);
	buff = get_next_line(fd);
	while (buff)
	{
		if (ft_strlen(buff) > 0 && buff[ft_strlen(buff) - 1] == '\n')
			buff[ft_strlen(buff) - 1] = '\0';
		ft_lst_add_back(&game->map, ft_lst_new(buff));
		buff = get_next_line(fd);
	}
}
