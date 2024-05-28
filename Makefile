# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:33:06 by janhan            #+#    #+#              #
#    Updated: 2024/05/28 17:17:09 by janhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		cub3d

CC				=		cc

CFLAGS			=		#-Wall -Wextra -Werror
INCLUDE			=		-Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
HEADER			=		./includes/header.h										\
						./includes/define.h

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
						./srcs_mand/1_init_utils/init_object.c						\
						./srcs_mand/1_init_utils/init_player.c						\
						./srcs_mand/1_init_utils/load_texture.c						\
						./srcs_mand/1_init_utils/multi_img_init.c					\
						./srcs_mand/2_hook_utils/key_hook.c							\
						./srcs_mand/2_hook_utils/mouse_handle.c						\
						./srcs_mand/3_ray_utils/get_dest.c							\
						./srcs_mand/3_ray_utils/get_dest_sub.c						\
						./srcs_mand/4_render_utils/get_texture.c					\
						./srcs_mand/4_render_utils/object_render.c					\
						./srcs_mand/4_render_utils/player_movement.c				\
						./srcs_mand/4_render_utils/render_intro.c					\
						./srcs_mand/4_render_utils/render_mini_map.c				\
						./srcs_mand/4_render_utils/render_player.c					\
						./srcs_mand/4_render_utils/render_texture.c					\
						./srcs_mand/4_render_utils/render3d.c						\
						./srcs_mand/4_render_utils/sprite_handle.c					\
						./srcs_mand/4_render_utils/update.c							\
						./srcs_mand/5_thread_utils/thread_utils.c					\
						./srcs_mand/utils/color_rgb.c								\
						./srcs_mand/utils/dist.c									\
						./srcs_mand/utils/draw_utils.c								\
						./srcs_mand/utils/end_program.c								\
						./srcs_mand/utils/error_exit.c								\
						./srcs_mand/utils/free.c									\
						./srcs_mand/utils/get_next_line.c							\
						./srcs_mand/utils/make_img.c
OBJS_MAND		=	$(SRCS_MAN:.c=.o)

SRCS_BONUS		=		print_info.c												\
						./srcs_bonus/main.c											\
						./srcs_bonus/0_parse/check_parse.c							\
						./srcs_bonus/0_parse/check_utils.c							\
						./srcs_bonus/0_parse/parse.c								\
						./srcs_bonus/0_parse/parse_utils.c							\
						./srcs_bonus/0_parse/parse_utils2.c							\
						./srcs_bonus/0_parse/parse_utils3.c							\
						./srcs_bonus/1_init_utils/init.c							\
						./srcs_bonus/1_init_utils/init_game.c						\
						./srcs_bonus/1_init_utils/init_map.c						\
						./srcs_bonus/1_init_utils/init_object.c						\
						./srcs_bonus/1_init_utils/init_player.c						\
						./srcs_bonus/1_init_utils/load_texture.c					\
						./srcs_bonus/1_init_utils/multi_img_init.c					\
						./srcs_bonus/2_hook_utils/key_hook.c						\
						./srcs_bonus/2_hook_utils/mouse_handle.c					\
						./srcs_bonus/3_ray_utils/get_dest.c							\
						./srcs_bonus/3_ray_utils/get_dest_sub.c						\
						./srcs_bonus/4_render_utils/get_texture.c					\
						./srcs_bonus/4_render_utils/object_render.c					\
						./srcs_bonus/4_render_utils/player_movement.c				\
						./srcs_bonus/4_render_utils/render_intro.c					\
						./srcs_bonus/4_render_utils/render_mini_map.c				\
						./srcs_bonus/4_render_utils/render_player.c					\
						./srcs_bonus/4_render_utils/render_texture.c				\
						./srcs_bonus/4_render_utils/render3d.c						\
						./srcs_bonus/4_render_utils/sprite_handle.c					\
						./srcs_bonus/4_render_utils/update.c						\
						./srcs_bonus/5_thread_utils/thread_utils.c					\
						./srcs_bonus/utils/color_rgb.c								\
						./srcs_bonus/utils/dist.c									\
						./srcs_bonus/utils/draw_utils.c								\
						./srcs_bonus/utils/end_program.c							\
						./srcs_bonus/utils/error_exit.c								\
						./srcs_bonus/utils/free.c									\
						./srcs_bonus/utils/get_next_line.c							\
						./srcs_bonus/utils/make_img.c
OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)

ifdef FLAG
	OBJS_FILES = $(OBJS_BONUS)
else
	OBJS_FILES = $(OBJS_MAND)
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
	@echo $(CURSIVE)$(YELLOW) "      - Making $(NAME) Game -" $(NONE)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(LIBFT_A) $(INCLUDE)  $^ -o $@
	@install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
	@echo $(CURSIVE)$(YELLOW) "        - Compiling $(NAME) -" $(NONE)
	@echo $(GREEN) "            - Complete -"$(NONE)

%.o : %.c $(HEADER)
	@echo $(CURSIVE)$(YELLOW) "      - Making object files -" $(NONE)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -fr $(OBJS_MAND) $(OBJS_BONUS)
	@make clean -C $(LIBFT_DIR)
	@echo $(CURSIVE)$(BLUE) "     - clean OBJ files -" $(NONE)

fclean : clean
	@rm -fr $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo $(CURSIVE)$(PURPLE)"      - clean $(NAME) file -"$(NONE)

re	:
	@make -C $(LIBFT_DIR)
	@make fclean
	@make all

.PHONY: all make clean fclean bonus re

