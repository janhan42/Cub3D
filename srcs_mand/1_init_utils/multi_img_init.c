/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_img_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:45:54 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:41:50 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

static void	init_multi_png_sub(t_game *game, t_img *img, char *path)
{
	img->img = mlx_png_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (img->img == NULL)
		error_exit("init_mulit_img_sub mlx_png_file_to_img failed");
	img->addr = mlx_get_data_addr(img->img, &img->bit_per_pixel,
			&img->line_length, &img->endian);
	free(path);
}

void	init_multi_png_img(t_game *game, t_img **img, char *file_path, int size)
{
	int		i;
	char	*temp;
	char	*num;
	char	*result;

	i = 0;
	while (i < size)
	{
		img[i] = (t_img *)malloc(sizeof(t_img));
		if (img[i] == NULL)
			error_exit("init_multi_img malloc failed");
		num = ft_itoa(i);
		if (num == NULL)
			error_exit("init_multi_img ft_itoa failed");
		temp = ft_strjoin(file_path, num);
		free(num);
		if (temp == NULL)
			error_exit("ini_multi_img ft_strjoin failed");
		result = ft_strjoin(temp, ".png");
		free(temp);
		if (result == NULL)
			error_exit("ini_multi_img ft_strjoin failed");
		init_multi_png_sub(game, img[i], result);
		i++;
	}
}

static void	init_multi_xpm_sub(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (img->img == NULL)
		error_exit("init_mulit_img_sub mlx_xpm_file_to_img failed");
	img->addr = mlx_get_data_addr(img->img, &img->bit_per_pixel,
			&img->line_length, &img->endian);
	free(path);
}

void	init_multi_xpm_img(t_game *game, t_img **img, char *file_path, int size)
{
	int		i;
	char	*temp;
	char	*num;
	char	*result;

	i = 0;
	while (i < size)
	{
		img[i] = (t_img *)malloc(sizeof(t_img));
		if (img[i] == NULL)
			error_exit("init_multi_img malloc failed");
		num = ft_itoa(i);
		if (num == NULL)
			error_exit("init_multi_img ft_itoa failed");
		temp = ft_strjoin(file_path, num);
		free(num);
		if (temp == NULL)
			error_exit("ini_multi_img ft_strjoin failed");
		result = ft_strjoin(temp, ".xpm");
		free(temp);
		if (result == NULL)
			error_exit("ini_multi_img ft_strjoin failed");
		init_multi_xpm_sub(game, img[i], result);
		i++;
	}
}
