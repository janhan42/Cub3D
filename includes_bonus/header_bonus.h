/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:25:54 by sangshin          #+#    #+#             */
/*   Updated: 2024/06/17 14:10:19 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "define_bonus.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/_pthread/_pthread_t.h>
# include <sys/_types/_ssize_t.h>

typedef enum e_game_mode
{
	INTRO,
	GAME,
	DIE,
	MENU,
}	t_game_mode;

typedef enum e_object_type
{
	GREEN_LIGHT,
	RED_LIGHT,
	NOMAL_LIGHT,
	HORIZONTAL_DOOR,
	VERTICAL_DOOR,
}	t_object_type;

typedef enum e_wall_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR,
	DOOR1,
	DOOR2,
	DOOR3,
}	t_wall_type;

typedef struct s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

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

typedef struct s_single_minimap
{
	int	mx;
	int	my;
	int	x;
	int	y;
}	t_single_minimap;

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
	int		is_h_door;
	double	distance_v;
	int		is_v_door;
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

typedef struct s_mouse
{
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
}	t_mouse;

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	player_rad;
	int		player_fov_off_y;
	int		shot;
	int		npc_hit;
	int		shot_sound;
	int		shot_frame;
	int		shot_time;
	int		move_w;
	int		move_s;
	int		move_a;
	int		move_d;
	t_img	**shotgun;
}	t_player;

typedef struct s_object
{
	t_object_type	type;
	int				state;
	double			object_x;
	double			object_y;
	double			object_z;
	t_img			*img;
	double			img_pos_x;
	double			img_pos_y;
	double			img_pos_z;
	double			distance;
	int				frame;
	int				max_frame;
}	t_object;

typedef struct s_draw_obj
{
	t_object		*target;
	int				height;
	int				width;
	int				screen_x;
	int				object_start_x;
	int				object_end_x;
	int				render_x;
	int				start_y;
	int				dest_y;
	double			angle_diff;
	double			object_rad;
	double			player_left;
	double			player_right;
	double			step_x;
	double			step_y;
	double			scale;
	unsigned int	color;
}	t_draw_obj;

typedef struct s_draw_door
{
	t_object		*target;
	int				width;
	double			height;
	int				screen_x;
	int				render_x;
	int				start_y;
	int				dest_y;
	int				door_start;
	int				door_end;
	double			player_door_rad;
	double			door_rad;
	double			angle_diff;
	double			h_offset;
	double			current_height;
	double			step_x;
	double			step_y;
	double			one_step_x;
	double			one_step_y;
	double			rad_diff;
	unsigned int	color;
}	t_draw_door;

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

typedef enum e_npc_type
{
	CACO_DEMON,
}	t_npc_type;

typedef enum e_npc_state
{
	IDLE,
	WALK,
	ATTACK,
	PAIN,
	DEATH,
}	t_npc_state;

typedef struct s_npc_ray
{
	double	dx;
	double	dy;
	double	distance;
	double	angle;
	double	x;
	double	y;
	int		map_x;
	int		map_y;
	int		i;
}	t_npc_ray;

typedef struct s_npc_update
{
	int		ray_flag;
	double	next_x;
	double	next_y;
	double	angle;
	double	dx;
	double	dy;
}	t_npc_update;

typedef struct s_npc
{
	t_npc_type		type;
	t_npc_state		state;
	double			npc_x;
	double			npc_y;
	double			npc_z;
	double			distance;
	int				frame;
	int				frame_max;
	int				frame_time;
	int				hp;
}	t_npc;

typedef struct s_draw_npc
{
	t_npc			*target;
	int				height;
	int				width;
	int				screen_x;
	int				npc_start_x;
	int				npc_end_x;
	int				render_x;
	int				start_y;
	int				dest_y;
	double			angle_diff;
	double			npc_rad;
	double			player_left;
	double			player_right;
	double			step_x;
	double			step_y;
	double			scale;
	unsigned int	color;
}	t_draw_npc;

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
	t_img		*minimap_img;
	t_img		*render;
	t_img		*main_background;
	t_img		*start_n;
	t_img		*start_h;
	t_img		*exit_game_n;
	t_img		*exit_game_h;
	t_img		*main_menu;
	t_img		*intro;
	t_mouse		*mouse;
	t_ray_dest	*ray_info;
	t_player	*player;
	t_game_mode	mode;
	int			full_map;
	int			map_resizing;
	int			full_map_x;
	int			full_map_y;
	int			w_dist[WINDOW_W];
	t_object	**objects;
	t_img		***object_texture;
	int			object_count;
	t_img		*texture;
	pthread_t	sound_test;
	pthread_t	sound_test_theme;
	int			pthread_kill;
	double		frame_time;
	int			frame;
	int			s_time;
	int			npc_count;
	t_npc		**npcs;
	t_img		****npc_texture;
	pthread_t	npc_sound;
	int			npc_sound_flag;
	int			npc_death_flag;
	int			npc_attack_flag;
	t_img		*blood;
	int			blood_flag;
}	t_game;

/*************************************************************/
/*========                   parse                   ========*/
/*************************************************************/
int		parse_file(t_game *game, const char *cub_file_path);
int		parse_color(int *cf, char *line);
int		parse_map(t_parse *parse);
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
void	init_multi_xpm_img(t_game *game,
			t_img **img, char *file_path, int size);
void	init_multi_png_img(t_game *game,
			t_img **img, char *file_path, int size);
void	load_texture(t_game *game);
void	init_object(t_game *game);
void	init_npc(t_game *game);
/*************************************************************/
/*========                 ray utils                 ========*/
/*************************************************************/
t_dest	get_dest(double x, double y, double rad, t_game *game);
void	check_horizion_init(double x, double y, double rad, t_ray_dest *ray);
void	check_vertical_init(double x, double y, double rad, t_ray_dest *ray);
int		npc_ray(t_player *player, t_npc *npc, t_game *game);
/*************************************************************/
/*========                 event hook                ========*/
/*************************************************************/
int		key_hook(int keycode, t_game *game);
int		key_hook_release(int keycode, t_game *game);
int		mouse_handle(int button, int x, int y, t_game *game);

/*************************************************************/
/*========                render utils               ========*/
/*************************************************************/

int		update(t_game *game);

// 0_intro
void	render_intro(t_game *game);

// 1_game
void	draw_door(t_object **obj, int cnt, t_player *player, t_game *game);

// NPC
void	render_npc(t_game *game);
void	set_npc_info(t_draw_npc *info, t_player *player, t_game *game);
void	calculate_npc_dist(t_npc **npc, t_player *player, int cnt);
int		compare_npc(const void *a, const void *b);
void	update_npc(t_npc *npc, t_player *player, t_game *game);
void	shot_npc(t_draw_npc *info, t_game *game,
			t_player *player, int *limiter);
void	frame_npc(t_draw_npc *info, t_game *game, int limiter);

int		get_door_width(t_object *door, t_player *player);
void	get_door_height_horizion(t_player *player, t_object *door,
			double *longer, double *smaller);
double	get_door_height(t_object *door, t_player *player, int width,
			double *offset);
void	set_door_info_sub(t_draw_door *info);
void	set_door_info(t_draw_door *info, t_player *player);
void	render_object(t_game *game);
void	game_mouse_update(t_game *game);
void	render_game(t_game *game);
void	player_movement(t_game *game);
int		compare(const void *a, const void *b);
void	calculate_obj_dist(t_object **obj, t_player *player, int cnt);
void	set_obj_info(t_draw_obj *info, t_player *player, t_game *game);
double	wall_collision(t_game *game, int state);
void	render(t_game *game, double distance, int time, int side);
void	render_texture(t_game *game, t_dest *dest, int t);
void	render_3d(t_game *game);
void	draw_map_squre(t_game *game, t_single_minimap *m);
void	render_mini_map(t_game *game);
void	render_mini_map_center(t_game *game);
void	render_map_player(t_img *img, t_game *game);
void	render_map_player_center(t_img *img, t_game *game);
int		render_weapon(t_game *game);
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
void	draw_line(t_img *img, t_2dot dots, int color);
void	draw_square_on_img(t_img *img, int x, int y, int color);
void	put_pixel_on_img(t_img	*img, int x, int y, int color);
void	one_line(t_img *img, t_2dot *dots, int color);
void	scale_texture(t_img *src, t_img *dst, float scale_factor);
int		color_spoid(int x, int y, t_img *img);
void	int_to_rgb(int rgb, int *r, int *g, int *b);
int		rgb_to_int(int r, int g, int b);

// 1_trash
double	dist(double x, double y, double hx, double hy);

// 2_end_program
void	kill_sound(int sig);
int		end_program(t_game *game);
int		key_press(int key, t_game *game);
void	error_exit(char *msg);

// 3_free
void	str_free(char *str);
void	free_memory(void *memory);
int		free_memory_return(void *memory, int return_code);
void	free_array_memory(void **memory, int index);

/*************************************************************/
/*========               pthread utils               ========*/
/*************************************************************/
void	*sound_handle(void *game);
void	*sound_theme(void	*game);
void	*sound_npc(void *game);

#endif
