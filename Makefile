# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:33:06 by janhan            #+#    #+#              #
#    Updated: 2024/05/27 07:58:16 by janhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		cub3d

CC				=		cc

CFLAGS			=		-Wall -Wextra -Werror
INCLUDE			=		-Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
HEADER			=		./includes/header.h										\
						./includes/define.h

LIBFT_DIR		=		libft
LIBFT_A			=		libft/libft.a

MLX_DIR			=		mlx

# SRCS_MAN		=		./test.c

SRCS_MAN		=		./srcs/main.c											\
						./srcs/0_init_utils/init_game.c							\
						./srcs/0_init_utils/init_map.c							\
						./srcs/0_init_utils/init_object.c						\
						./srcs/0_init_utils/init_player.c						\
						./srcs/0_init_utils/load_texture.c						\
						./srcs/0_init_utils/multi_img_init.c					\
						./srcs/1_ray_utils/get_dest.c							\
						./srcs/2_hook_utils/key_hook.c							\
						./srcs/2_hook_utils/mouse_handle.c						\
						./srcs/3_render_utils/object_render.c					\
						./srcs/3_render_utils/rendering.c						\
						./srcs/3_render_utils/sprite_handle.c					\
						./srcs/3_render_utils/update.c							\
						./srcs/4_thread_utils/thread_utils.c					\
						./srcs/utils/color_rgb.c								\
						./srcs/utils/dist.c										\
						./srcs/utils/draw_utils.c								\
						./srcs/utils/end_program.c								\
						./srcs/utils/error_exit.c								\
						./srcs/utils/make_img.c									\
						./srcs/utils/print_info.c
OBJS_MAND		=	$(SRCS_MAN:.c=.o)

SRCS_BONUS		=
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

