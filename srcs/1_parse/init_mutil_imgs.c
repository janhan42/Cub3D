/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutil_imgs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:33:58 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 13:43:02 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	path_name2(char *path, int i, int len)
{
	int j;

	j = len;
	path[j++] = '0' + i / 10;
	path[j++] = '0' + i % 10;
	path[j++] = '.';
	path[j++] = 'x';
	path[j++] = 'p';
	path[j++] = 'm';
	path[j++] = 0;
}

void	init_gun(int o, int len, char *path, t_game *game)
{
	int i;

	i = 0;
	while (++i < len)
	{
		path_name2(path, i, 12);
		game->data->gun[o].gun[i - 1].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 500, 400);
		game->data->gun[o].gun[i - 1].addr = mlx_get_data_addr(game->data->gun[o].gun[i - 1].mlx_img, &game->data->gun[o].gun[i - 1].bpp, &game->data->gun[o].gun[i - 1].line_len, &game->data->gun[o].gun[i - 1].endian);
		paint_img(game, game->data->gun[o].gun + i - 1, path, 500, 400);
	}
}

void	init_guns(t_game *game)
{
	char	path[100];

	ft_memcpy(path, "img/guns/g1/", 12);
	init_gun(4, 53, path, game);

	ft_memcpy(path, "img/guns/g2/", 12);
	init_gun(9, 15, path, game);

	ft_memcpy(path, "img/guns/g3/", 12);
	init_gun(2, 34, path, game);

	ft_memcpy(path, "img/guns/g4/", 12);
	init_gun(19, 50, path, game);

	ft_memcpy(path, "img/guns/g5/", 12);
	init_gun(13, 27, path, game);

	ft_memcpy(path, "img/guns/g6/", 12);
	init_gun(15, 18, path, game);

	ft_memcpy(path, "img/guns/g9/", 12);
	init_gun(17, 82, path, game);

	ft_memcpy(path, "img/guns/g7/", 12);
	init_gun(20, 25, path, game);

	ft_memcpy(path, "img/guns/g8/", 12);
	init_gun(5, 27, path, game);
}

void	init_motion_imgs(t_game *game, int o, int len, char *s, int path_len)
{
	int i;
	char path[100];

	ft_memcpy(path, s, path_len);
	i = 0;
	while (++i < len)
	{
		path_name2(path, i, path_len);
		game->data->motion[o].frm[i - 1].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, path, &(game->data->motion[o].frm[i - 1].x), &(game->data->motion[o].frm[i - 1].y));
		game->data->motion[o].frm[i - 1].addr = mlx_get_data_addr(game->data->motion[o].frm[i - 1].mlx_img, &game->data->motion[o].frm[i - 1].bpp, &game->data->motion[o].frm[i - 1].line_len, &game->data->motion[o].frm[i - 1].endian);
	}
	game->data->motion[o].frame = len - 1;
}

void	init_motion(t_game *game)
{
	init_motion_imgs(game, 0, 17, "img/enemies/run/", 16);
	init_motion_imgs(game, 1, 29, "img/enemies/walk/", 17);
	init_motion_imgs(game, 2, 51, "img/enemies/attack_1/", 21);
	init_motion_imgs(game, 3, 64, "img/enemies/attack_2/", 21);
	init_motion_imgs(game, 4, 87, "img/enemies/attack_3/", 21);
	init_motion_imgs(game, 5, 34, "img/enemies/hit/", 16);
	init_motion_imgs(game, 6, 82, "img/enemies/death/", 18);
}
