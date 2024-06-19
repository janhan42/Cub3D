/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:33:01 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 11:50:13 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_BONUS_H
# define DEFINE_BONUS_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1

/*************************************************************/
/*========                 game info                 ========*/
/*************************************************************/

# define PIXEL 64
# define MINI_MAP_PIXEL 32
# define WINDOW_W 1920
# define WINDOW_H 1080
# define MAX_DISTANCE 10000
# define MAP_SIZE_UP 2
# define MAP_SIZE_DOWN 3

/*************************************************************/
/*========               parse define                ========*/
/*************************************************************/

/* texture */
# define T_NO 0
# define T_SO 1
# define T_WE 2
# define T_EA 3
# define T_FLOOR 4
# define T_CEIL 5
# define T_MAP 6
# define T_DOOR 7
# define TEXTURE_COUNT 4
# define NO_COLOR	0xFF00FF
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

/*************************************************************/
/*========               keyboard code               ========*/
/*************************************************************/
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define M_LEFT_CLICK 600
# define M_RIGHT_CLICK 601
# define M_UP 500
# define M_DOWN 501
# define M_LEFT 502
# define M_RIGHT 503
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_T 17
# define KEY_Y 16
# define KEY_U 32
# define KEY_I 34
# define KEY_O 31
# define KEY_P 35
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_N 45
# define KEY_M 46
# define TAB 48
# define CAPS 272
# define SHIFT 257
# define ESC 53
# define SPACE 49
# define ENTER 36
# define F1 122
# define CONTROL 269
# define WINDOW_CLOSE	17
# define KEY_PRESS 2
# define KEY_RELEASE 3

/*************************************************************/
/*========              minimap define               ========*/
/*************************************************************/
# define MINI_MAP_RADIUS 5
# define OPEN 22
# define CLOSE 32

/*************************************************************/
/*========              wall collision               ========*/
/*************************************************************/
# define PLUS 4
# define MINUS 0
# define SIN 2
# define COS 0
# define X 1
# define Y 0
#endif
