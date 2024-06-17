/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_mand.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:25:54 by sangshin          #+#    #+#             */
/*   Updated: 2024/06/17 13:51:14 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_MAND_H
# define HEADER_MAND_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "define_mand.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/_types/_ssize_t.h>

typedef enum e_wall_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_wall_type;

typedef struct s_vec2d
{
	double	x;
	double	y;
}	t_vec2d;

typedef struct s_single_scale
{
	int		x;
	int		y;
	int		new_x;
	int		new_y;
	int		color;
	float	scale;
}	t_single_scale;

typedef struct s_single_texuture
{
	int		wall_x;
	int		wall_y;
	int		texture_x;
	int		line_h;
	double	step;
	int		color;
	int		x;
	int		y;
	int		h_offset;
	double	step_y;
}	t_single_texture;

typedef struct s_single_parse
{
	int		fd;
	int		gnl_ret;
	int		parse_type;
	char	*line;
}	t_single_parse;

typedef struct s_gnl
{
	char	*buf;
	char	*temp;
	ssize_t	offset;
	ssize_t	index;
}	t_gnl;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_ray_dest
{
	double	*ray_result;
	double	rx;
	double	ry;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	xo;
	double	yo;
	double	distance_h;
	double	distance_v;
	double	a_tan;
	double	n_tan;
	int		mx;
	int		my;
	int		dof;
}	t_ray_dest;

typedef struct s_dest
{
	int		x;
	int		y;
	double	distance;
	int		wall_type;
	double	offset;
	int		y_vert;
	int		x_hor;
}	t_dest;

typedef struct s_2dot
{
	int	start_x;
	int	start_y;
	int	dest_x;
	int	dest_y;
}	t_2dot;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	player_rad;
	int		move_w;
	int		move_s;
	int		move_a;
	int		move_d;
}	t_player;

typedef struct s_texture
{
	int		*texture;
	char	*tex_path;
	double	width;
	double	height;
}	t_texture;

typedef struct s_parse
{
	int			is_d;
	int			is_f;
	int			is_c;
	int			floor_color;
	int			ceiling_color;
	int			row;
	int			col;
	char		*temp_map;
	char		**map;
	t_texture	tex[TEXTURE_COUNT];
}	t_parse;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			map_len_w;
	int			map_len_h;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceiling_color;
	t_parse		parse;
	t_img		*render;
	t_ray_dest	*ray_info;
	t_player	*player;
	t_img		*texture;
	double		frame_time;
	int			frame;
	int			s_time;
}	t_game;

/*************************************************************/
/*========                   parse                   ========*/
/*************************************************************/
int		parse_file(t_game *game, const char *cub_file_path);
int		parse_color(int *cf, char *line);
int		parse_map(t_parse *parse, char *temp_map);
char	*update_map(char *s1, char *s2);
char	*parse_path_malloc(char *line);
// _valid
int		is_cub_file(const char *cub_file_path);
int		is_space(char c);
int		is_upper(char c);
int		is_space_around_position(t_game *game, int row, int col);
int		is_blank_line(char *line);
int		is_map_valid(char *line);
int		find_char(const char *value, char c);
// _check
int		check_tex(t_game *game);
int		check_parse(t_game *game);

/*************************************************************/
/*========                   init                    ========*/
/*************************************************************/
void	init(t_game *game, int ac, char **av);
void	init_map(t_game *game);
void	init_game(t_game *game);
void	init_player(t_game *game);
void	load_texture(t_game *game);

/*************************************************************/
/*========                 ray utils                 ========*/
/*************************************************************/
t_dest	get_dest(double x, double y, double rad, t_game *game);
void	check_horizion_init(double x, double y, double rad, t_ray_dest *ray);
void	check_vertical_init(double x, double y, double rad, t_ray_dest *ray);

/*************************************************************/
/*========                 event hook                ========*/
/*************************************************************/
int		key_hook(int keycode, t_game *game);
int		key_hook_release(int keycode, t_game *game);

/*************************************************************/
/*========                render utils               ========*/
/*************************************************************/

int		update(t_game *game);

// 1_game
void	player_movement(t_game *game);
void	render_texture(t_game *game, t_dest *dest, int t);
void	render(t_game *game, double distance, int time, int side);

void	render_3d(t_game *game);
t_img	*get_texture(t_game *game, t_dest *dest);

/*************************************************************/
/*========                   utils                   ========*/
/*************************************************************/
// _init_utils
t_img	*make_image(t_game *game, int width, int height);
t_img	*make_xpm_img(t_game *game, char *file_path);
t_img	make_png_img_nomalloc(t_game *game, char *file_path);

// _gnl
char	*get_next_line(int fd);
char	*reader(char **string, int fd);
char	*join(char *string, char *buf);
char	*cutter_cal(char **string);
char	*rose_knife(char *string, int i);

// 0_draw_utils
void	draw_square_on_img(t_img *img, int x, int y, int color);
void	put_pixel_on_img(t_img	*img, int x, int y, int color);
void	scale_texture(t_img *src, t_img *dst, float scale_factor);
void	render_sprite_object(t_game *game);
int		color_spoid(int x, int y, t_img *img);
void	int_to_rgb(int rgb, int *r, int *g, int *b);
int		rgb_to_int(int r, int g, int b);

// 1_trash
double	dist(double x, double y, double hx, double hy);

// 2_end_program
int		end_program(t_game *game);
int		key_press(int key, t_game *game);
void	error_exit(char *msg);

// 3_free
void	str_free(char *str);
void	free_memory(void *memory);
int		free_memory_return(void *memory, int return_code);
void	free_array_memory(void **memory, int index);

#endif
