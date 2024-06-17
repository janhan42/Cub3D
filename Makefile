# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:33:06 by janhan            #+#    #+#              #
#    Updated: 2024/06/17 13:46:49 by sangshin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		cub3D

CC				=		cc

CFLAGS			=		-g -Wall -Wextra -Werror #-fsanitize=address
INCLUDE			=		-Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
HEADER_MAND		=		./includes_mand/header_mand.h							\
						./includes_mand/define_mand.h
HEADER_BONUS	=		./includes_bonus/header_bonus.h							\
						./includes_bonus/define_bonus.h
LIBFT_DIR		=		libft
LIBFT_A			=		libft/libft.a

MLX_DIR			=		mlx

# SRCS_MAN		=		./test.c

SRCS_MAN		=		./srcs_mand/main.c											\
						./srcs_mand/0_parse/check_parse.c							\
						./srcs_mand/0_parse/check_utils.c							\
						./srcs_mand/0_parse/parse.c									\
						./srcs_mand/0_parse/parse_utils.c							\
						./srcs_mand/0_parse/parse_utils2.c							\
						./srcs_mand/0_parse/parse_utils3.c							\
						./srcs_mand/1_init_utils/init.c								\
						./srcs_mand/1_init_utils/init_game.c						\
						./srcs_mand/1_init_utils/init_map.c							\
						./srcs_mand/1_init_utils/init_player.c						\
						./srcs_mand/1_init_utils/load_texture.c						\
						./srcs_mand/1_init_utils/multi_img_init.c					\
						./srcs_mand/2_hook_utils/key_hook.c							\
						./srcs_mand/3_ray_utils/get_dest.c							\
						./srcs_mand/3_ray_utils/get_dest_sub.c						\
						./srcs_mand/4_render_utils/get_texture.c					\
						./srcs_mand/4_render_utils/player_movement.c				\
						./srcs_mand/4_render_utils/render_texture.c					\
						./srcs_mand/4_render_utils/render3d.c						\
						./srcs_mand/4_render_utils/update.c							\
						./srcs_mand/utils/color_rgb.c								\
						./srcs_mand/utils/dist.c									\
						./srcs_mand/utils/draw_utils.c								\
						./srcs_mand/utils/end_program.c								\
						./srcs_mand/utils/error_exit.c								\
						./srcs_mand/utils/free.c									\
						./srcs_mand/utils/get_next_line.c							\
						./srcs_mand/utils/make_img.c
OBJS_MAND		=	$(SRCS_MAN:.c=.o)

SRCS_BONUS		=		./srcs_bonus/main_bonus.c										\
						./srcs_bonus/0_parse/check_parse_bonus.c						\
						./srcs_bonus/0_parse/check_utils_bonus.c						\
						./srcs_bonus/0_parse/parse_bonus.c								\
						./srcs_bonus/0_parse/parse_utils_bonus.c						\
						./srcs_bonus/0_parse/parse_utils2_bonus.c						\
						./srcs_bonus/0_parse/parse_utils3_bonus.c						\
						./srcs_bonus/1_init_utils/init_bonus.c							\
						./srcs_bonus/1_init_utils/init_game_bonus.c						\
						./srcs_bonus/1_init_utils/init_map_bonus.c						\
						./srcs_bonus/1_init_utils/init_npc_bonus.c						\
						./srcs_bonus/1_init_utils/init_object_bonus.c					\
						./srcs_bonus/1_init_utils/init_player_bonus.c					\
						./srcs_bonus/1_init_utils/load_texture_bonus.c					\
						./srcs_bonus/1_init_utils/multi_img_init_bonus.c				\
						./srcs_bonus/2_hook_utils/key_hook_bonus.c						\
						./srcs_bonus/2_hook_utils/mouse_handle_bonus.c					\
						./srcs_bonus/3_ray_utils/get_dest_bonus.c						\
						./srcs_bonus/3_ray_utils/get_dest_sub_bonus.c					\
						./srcs_bonus/3_ray_utils/npc_ray_bonus.c						\
						./srcs_bonus/4_render_utils/get_texture_bonus.c					\
						./srcs_bonus/4_render_utils/render_npc_bonus.c					\
						./srcs_bonus/4_render_utils/render_npc_sub_bonus.c				\
						./srcs_bonus/4_render_utils/update_npc_bonus.c					\
						./srcs_bonus/4_render_utils/render_object_bonus.c				\
						./srcs_bonus/4_render_utils/render_object_sub_bonus.c			\
						./srcs_bonus/4_render_utils/render_door_bonus.c					\
						./srcs_bonus/4_render_utils/render_door_sub_bonus.c				\
						./srcs_bonus/4_render_utils/player_movement_bonus.c				\
						./srcs_bonus/4_render_utils/render_intro_bonus.c				\
						./srcs_bonus/4_render_utils/render_mini_map_bonus.c				\
						./srcs_bonus/4_render_utils/render_mini_map_sub_bonus.c			\
						./srcs_bonus/4_render_utils/render_player_bonus.c				\
						./srcs_bonus/4_render_utils/render_texture_bonus.c				\
						./srcs_bonus/4_render_utils/render3d_bonus.c					\
						./srcs_bonus/4_render_utils/sprite_handle_bonus.c				\
						./srcs_bonus/4_render_utils/update_bonus.c						\
						./srcs_bonus/5_thread_utils/thread_utils_bonus.c				\
						./srcs_bonus/utils/color_rgb_bonus.c							\
						./srcs_bonus/utils/dist_bonus.c									\
						./srcs_bonus/utils/draw_utils_bonus.c							\
						./srcs_bonus/utils/end_program_bonus.c							\
						./srcs_bonus/utils/error_exit_bonus.c							\
						./srcs_bonus/utils/free_bonus.c									\
						./srcs_bonus/utils/get_next_line_bonus.c						\
						./srcs_bonus/utils/make_img_bonus.c
OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)

ifdef FLAG
	OBJS_FILES = $(OBJS_BONUS)
	HEADER = $(HEADER_BONUS)
else
	OBJS_FILES = $(OBJS_MAND)
	HEADER = $(HEADER_MAND)
endif

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
PURPLE='\033[35m'
BLUE='\033[34m'
DELETELINE='\033[K;

all : $(NAME)

bonus :
	make all FLAG=1

$(NAME) : $(OBJS_FILES)
	@echo $(CURSIVE)$(YELLOW) "		- Making $(NAME) Game -" $(NONE)
	@make -C $(LIBFT_DIR)
	@make -S -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(LIBFT_A) $(INCLUDE)  $^ -o $@
	@install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
	@echo $(CURSIVE)$(YELLOW) "		- Compiling $(NAME) -" $(NONE)
	@echo $(GREEN) "		- Complete -"$(NONE)

%.o : %.c $(HEADER)
	@echo $(CURSIVE)$(YELLOW) "		- Making object files -" $(NONE)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -fr $(OBJS_MAND) $(OBJS_BONUS)
	@make clean -S -C $(LIBFT_DIR)
	@echo $(CURSIVE)$(BLUE) "		- clean OBJ files -" $(NONE)

fclean : clean
	@rm -fr $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make clean -S -C $(MLX_DIR)
	@echo $(CURSIVE)$(PURPLE)"		- clean $(NAME) file -"$(NONE)

re	:
	@make -C $(LIBFT_DIR)
	@make fclean
	@make all

.PHONY: all make clean fclean bonus re
