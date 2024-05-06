/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:57:06 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 15:42:56 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include "../srcs/libft/libft.h"
# include "../mlx/mlx.h"
# include "../srcs/gnl/get_next_line.h"
# include "struct.h"
# include "defines.h"


/* 0_init */
int	start(t_game *game, int ac, char **av);
void	init_maps(char **av, t_game *game);
/* 1_PARSE */
void	check_argument(int ac, char **av);
void	init_map_info_sup(t_game *game, int i, int j);
void	parse_map_sub(t_game *game);
void	init_map_info(t_game *game, int i, int j);
void	check_map(t_game *game);
void	parse_map(t_game *game);
void	parsing(t_game *game);
void	paint_img(t_game *game, t_img *img, char *path, int res_x, int res_y);
void	img_pix_put(t_img *img, int x, int y, int color);
void	init_guns(t_game *game);
void	init_motion(t_game *game);
void	paint_color(t_img *img, int color, int x_s, int y_s);
void	init_angles(t_game *game);
void	up(t_data *data);
void	set_char_to_win(t_game *game);
void	down(t_data *data);
int		key_not_in_use(int key, t_game *game);
void	right_angle(t_game *game, t_data *data);
void	left_angle(t_game *game, t_data *data);
void	right(t_data *data);
void	left(t_data *data);
int		mouse_move(int x, int y, void *w, t_game *game);
void	mouse_move_map(int x, int y, t_game *game);
void	inc_get_minimap_color2(int x, int y, int angle, t_game *game);
void	mouse_move_game(int x, int y, t_game *game);
void	mouse_move_control(int x, int y, t_game *game);
void	mouse_move_setting(int x, int y, t_game *game);
void	mouse_move_intro(int x, int y, t_game *game);
int		mouse_press(int key, int x, int y, void *w, t_game *game);
int		set_design(int side, double x, double y, char design, t_game *game);
void	cast_to_3d(int i, t_game *game);
/* 2_run */
int		input(int key, t_game *game);
/* UTILS */
void	error_exit(char *str);
int		error_return(char *str);
t_map	*ft_lst_last(t_map *lst);
void	ft_lst_del_one(t_map *lst, void(*del)(void*));
void	ft_lst_clear(t_map **lst, void (*del)(void*));
void	ft_lst_add_back(t_map **lst, t_map *new_node);
void	ft_lst_add_front(t_map **lst, t_map *new_node);
t_map	*ft_lst_new(void *content);
int		ft_lst_size(t_map *lst);

#endif
