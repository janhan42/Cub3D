# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 11:52:46 by janhan            #+#    #+#              #
#    Updated: 2024/05/06 14:14:40 by janhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		Cub3d

CC				=		cc

CFLAGS			=		-Wall -Wextra -Werror #-fsanitize
INCLUDE			=		-Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx

LIBFT_DIR		=		srcs/libft
LIBFT_A			=		srcs/libft/libft.a

MLX_DIR			=		mlx

SRCS			=		./cub3d.c							\
						./srcs/0_init/ft_init_maps.c		\
						./srcs/1_parse/check_argument.c		\
						./srcs/1_parse/parsing.c			\
						./srcs/1_parse/parsing_sub.c		\
						./srcs/1_parse/init_mutil_imgs.c	\
						./srcs/2_run/input.c				\
						./srcs/gnl/get_next_line.c			\
						./srcs/gnl/get_next_line_utils.c	\
						./srcs/utils/error_exit.c			\
						./srcs/utils/ft_lst.c				\
						./srcs/utils/ft_lst_new.c

OBJ_DIR			=		./srcs/obj

OBJ_FILES		=		$(SRCS:.c=.o)

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
PURPLE='\033[35m'
BLUE='\033[34m'
DELETELINE='\033[K;

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	@echo $(CURSIVE)$(YELLOW) "      - Making $(NAME) Game -" $(NONE)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	@$(CC) $(LDFLAGS) $(LIBFT_A) $(INCLUDE)  $^ -o $@
	@install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
	@echo $(CURSIVE)$(YELLOW) "        - Compiling $(NAME) -" $(NONE)
	@echo $(GREEN) "            - Complete -"$(NONE)

%.o : %.c
	@echo $(CURSIVE)$(YELLOW) "      - Making object files -" $(NONE)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -fr $(OBJ_FILES)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo $(CURSIVE)$(BLUE) "     - clean OBJ files -" $(NONE)

fclean : clean
	@rm -fr $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo $(CURSIVE)$(PURPLE)"      - clean $(NAME) file -"$(NONE)

re	:
	@make -C $(LIBFT_DIR)
	@make fclean
	@make all

.PHONY: all make clean fclean re
