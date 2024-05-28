/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:25:54 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/29 00:03:09 by janhan           ###   ########.fr       */
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
# include <sys/_types/_ssize_t.h>

typedef enum e_game_mode
{
	INTRO,
	GAME,
	DIE,
	MENU,
}	e_game_mode;

typedef enum e_object_type
{
	GREEN_LIGHT,
	RED_LIGHT,
	NOMAL_LIGHT,
}	e_object_type;

typedef enum e_wall_type
{
	EAST,
	NORTH,
	WEST,
	SOUTH,
	DOOR,
	DOOR1,
	DOOR2,
	DOOR3,
}	e_wall_type;

typedef struct s_vec2i /* vector int */
{
	int x;
	int y;
}	t_vec2i;

typedef struct s_vec2d /* vector double */
{
	double x;
	double y;
}	t_vec2d;

typedef struct s_vec2u		/* vector usigned int */
{
	unsigned int x;
	unsigned int y;
}	t_vec2u;

/* Single ton */
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

typedef struct s_single_minimap
{
	int	mx;
	int	my;
	int	x;
	int	y;
}	t_single_minimap;
/*------------------------------*/

typedef struct s_ray_dest		/* ray 계산용 구조체 */
{
	double	*ray_result;		//	ray 계산값 (ray의 x, ray의 y, 직선의 거리) 저장
	double	rx;					//	ray 계산용 ray의 x 좌표
	double	ry;					//	ray 계산용 ray의 y 좌표
	double	hx;					//	ray 계산용 ray의 수평 x 좌표
	double	hy;					//	ray 계산용 ray의 수평 y 좌표
	double	vx;					//	ray 계산용 ray의 수직 x 좌표
	double	vy;					//	ray 계산용 ray의 수직 y 좌표
	double	xo;					//	ray 계산용 ray의 x 오프셋 값
	double	yo;					//	ray 계산용 ray의 y 오프셋 값
	double	distance_h;			//	ray 계산용 ray의 수평선에 대한 거리
	int		is_h_door;
	double	distance_v;			//	ray 계산용 ray의 수직선에 대한 거리
	int		is_v_door;
	double	a_tan;				//	ray 계산용 ray의 수평에서의 삼각함수 계산용
	double	n_tan;				//	ray 계산용 ray의 수직에서의 삼각함수 계산용
	int		mx;					//	ray 계산용 ray의 map에서의 x 좌표
	int		my;					//	ray 계산용 ray의 map에서의 y 좌표
	int		dof;				//	ray 계산용 ray의 계산 depth 조정
}	t_ray_dest;

typedef struct	s_dest /* ray 케이스팅 결과값 계산용 */
{
	int		x;				// 결과 ray의 x 좌표
	int		y;				// 결과 ray의 y 좌표
	double	distance;		// 결과 ray의 거리
	//int		direction;		// 결과 ray의 방향
	int		wall_type;
	double	offset;			// 결과 ray의 texture offset
	int		y_vert;			// 결과 ray의 수직일때 좌표
	int		x_hor;			// 결과 ray의 수평일때 좌표
}	t_dest;

typedef	struct	s_2dot /* pixel_put_img */
{
	int	start_x;		// 시작 x
	int	start_y;		// 시작 y
	int	dest_x;			// 도착 x
	int	dest_y;			// 도착 y
}	t_2dot;

typedef	struct	s_img		/* mlx 이미지 구조체 */
{
	void	*img;				// mlx_img mlx_***_to_image
	char	*addr;				// mlx_img mlx_get_data_addr
	int		bit_per_pixel;		// mlx_img mlx_get_data_addr
	int		line_length;		// mlx_img mlx_get_data_addr
	int		endian;				// mlx_img mlx_get_data_addr
	int		width;				// mlx_img mlx_get_data_addr
	int		height;				// mlx_img mlx_get_data_addr
}	t_img;

typedef struct s_mouse		/* mouse 이벤트 관리용 */
{
	int	x;						// mlx_get_mouse_pos
	int	y;						// mlx_get_mouse_pos
	int	prev_x;					// mlx_get_mouse_pos
	int	prev_y;					// mlx_get_mouse_pos
}	t_mouse;

typedef struct s_player		/* player info */
{
	double	player_x;			//	플레이어의 x 좌표
	double	player_y;			//	플레이어의 y 좌표
	double	player_rad;			//	플레이어의 각도
	int		player_fov_off_y;	//	플레이어의 마우스 수직방향용 오프셋
	int		shot;				//	플레이어의 총 발사용 bool 플레그 용도
	int		shot_sound;			//	플레이어의 총 발사음 bool 플레그 용도
	int		shot_frame;			//	플레이어의 총의 스프라이트를 위한 프레임
	int		shot_time;			//	플레이어의 총의 스프라이트를 위한 프레임 시간
	int		move_w;				//	플레이어의 이동 플레그
	int		move_s;				//	플레이어의 이동 플레그
	int		move_a;				//	플레이어의 이동 플레그
	int		move_d;				//	플레이어의 이동 플레그
	t_img	**shotgun;			//	플레이어의 총 스프라이트 이미지 **
}	t_player;

typedef struct s_object		/* object struct */
{
	e_object_type	type;		//	오브젝트 타입
	int				state;		//	오브젝트 상태
	double			object_x;	//	오브젝트 좌표 x
	double			object_y;	//	오브젝트 좌표 y
	double			object_z;
	t_img			*img;		//	그 오브젝트의 이미지
	double			img_pos_x;	//	이미지의 좌표 x
	double			img_pos_y;	//	이미지의 좌표 y
	double			img_pos_z;	//	이미지의 좌표 z
}	t_object;

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

typedef struct s_game		/* 메인 구조체 */
{
	void		*mlx;				//	mlx -> init_game()
	void		*mlx_win;			//	mlx window -> init_game()
	char		**map;				//	문자열로 읽어들인 맵 -> init_map()
	int			map_len_w;			//	MAP 의 최대 X의 길이 -> init_map()
	int			map_len_h;			//	MAP 의 최대 Y의 길이 ->init_map()
	int			map_width;			//	MAP X * IMG_SIZE -> init_map()
	int			map_height;			//	MAP Y * IMG_SIZE -> init_map()
	int			floor_color;		//	MAP 바닥 색상 -> init_map()
	int			ceiling_color;		//	MAP 천장 색상 -> init_map()
	t_parse		parse;
	t_img		*minimap_img;		//	좌측 상단 미니맵을 위한 mlx_img
	t_img		*render;			//	3DWall 을 위한 mlx_img
	t_img		*background;		//	배경(바닥, 천장)을 위한 mlx_img
	t_img		*main_background;	// 메인메뉴 백그라운드.
	t_img		*start_n;
	t_img		*start_h;
	t_img		*exit_game_n;
	t_img		*exit_game_h;
	t_img		*main_menu;			//	게임 시작 이전의 메인메뉴 mlx_img
	t_mouse		*mouse;				//	마우스 이벤트 관리 구조체
	t_ray_dest	*ray_info;			//	ray 계산용 구조체
	t_player	*player;			//	PLAYER 구조체
	e_game_mode	mode;				//	현재 게임 모드에 대한 상태값.
	int			full_map;
	int			map_resizing;
	int			full_map_x;
	int			full_map_y;
	/* TEST */
	t_object	**objects;
	t_img		*object_texture;
	int			object_count;
	t_img		*texture;			//	texture TEST
	pthread_t	sound_test;			//	sound TEST ptrhead
	pthread_t	sound_test_theme;	//	sound TEST ptrhead
	int			pthread_kill;		//	pthread kill flag
	double		frame_time;
	int			frame;
	int			s_time;
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
void	init_multi_xpm_img(t_game *game, t_img **img, char *file_path, int size);
void	init_multi_png_img(t_game *game, t_img **img, char *file_path, int size);
void	load_texture(t_game *game);

/*************************************************************/
/*========                 ray utils                 ========*/
/*************************************************************/
t_dest	*get_dest(double x, double y, double rad, t_game *game);
void	check_horizion_init(double x, double y, double rad, t_ray_dest *ray);
void	check_vertical_init(double x, double y, double rad, t_ray_dest *ray);

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
void	game_mouse_update(t_game *game);
void	render_game(t_game *game);
void	player_movement(t_game *game);

// void	draw_background(t_game *game);
double	wall_collision(t_game *game, int state);
void	render(t_game *game, double distance, int time, int side);
void	render_texture(t_game *game, t_dest *dest, int t);
int		color_spoid(int x, int y, t_img *img);
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

// _gnl
int	get_next_line(int fd, char **line);

// 0_draw_utils
void	draw_line(t_img *img, t_2dot dots, int color);
void	draw_square_on_img(t_img *img, int x, int y, int color);
void	put_pixel_on_img(t_img	*img, int x, int y, int color);
void	one_line(t_img *img, t_2dot *dots, int color);
void	scale_texture(t_img *src, t_img *dst, float scale_factor);
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

/*************************************************************/
/*========                print info                 ========*/
/*************************************************************/
void	print_mouse_info(t_mouse *mouse);
void	print_img_info(t_img *img, char *name);
void	print_player_info(t_player *player);
void	print_ray_result_info(double ray_result[4]);
void	print_ray_info(t_ray_dest *ray);
void	print_game_info(t_game *game);
void	print_object_info(t_object *object);
void	print_map_info(char **map);

/*************************************************************/
/*========                   TEST                    ========*/
/*************************************************************/
void	init_object(t_game *game);
t_img	*get_texture(t_game *game, t_dest *dest);
void	render_sprite_object(t_game *game);

#endif
