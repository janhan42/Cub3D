/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:57:06 by janhan            #+#    #+#             */
/*   Updated: 2024/05/04 13:48:57 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
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
