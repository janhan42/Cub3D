NAME	= cub3D

SRCS	=		main.c			\
				exit.c			\
				free.c			\
				get_next_line.c	\
				init.c			\
				is_valid.c		\
				is_valid2.c		\
				key.c			\
				parse_check.c	\
				parse_master.c	\
				parse_utils1.c	\
				parse_utils2.c	\
				parse.c			\
				render_3D.c		\
				render_master.c	\
				texture.c		\
				update_ray.c	\
				update.c		\
				utils.c			\
				utils2.c		\

SRC_PATH = ./src
SRC = $(addprefix $(SRC_PATH)/, $(SRCS))

OBJS	= $(SRCS:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJS))
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(CFLAG) $(HEADER) -o $@ -c $<

SRCS_BONUS =	main_bonus.c			\
				exit_bonus.c			\
				free_bonus.c			\
				get_next_line_bonus.c	\
				init_bonus.c			\
				is_valid_bonus.c		\
				is_valid2_bonus.c		\
				key_bonus.c				\
				map_bonus.c				\
				mouse_bonus.c			\
				parse_check_bonus.c		\
				parse_master_bonus.c	\
				parse_utils1_bonus.c	\
				parse_utils2_bonus.c	\
				parse_bonus.c			\
				render_3D_bonus.c		\
				render_master_bonus.c	\
				render_player_bonus.c	\
				render_ray_bonus.c		\
				sprite_bonus.c			\
				texture_bonus.c			\
				update_ray_bonus.c		\
				update_bonus.c			\
				utils_bonus.c			\
				utils2_bonus.c			\

SRC_BONUS_PATH = ./src_bonus
SRC_BONUS = $(addprefix $(SRC_BONUS_PATH)/, $(SRCS_BONUS))

OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJ_BONUS_PATH = ./obj_bonus
OBJ_BONUS = $(addprefix $(OBJ_BONUS_PATH)/, $(OBJS_BONUS))
$(OBJ_BONUS_PATH)/%.o: $(SRC_BONUS_PATH)/%.c
	@mkdir $(OBJ_BONUS_PATH) 2> /dev/null || true
	@gcc $(CFLAG) $(HEADER_BONUS) -o $@ -c $<

CC		= gcc
CFLAG	= -Wall -Wextra -Werror

RM		= rm -rf

HEADER	= -I./includes

HEADER_BONUS = -I./includes_bonus

MLX	= -framework OpenGL -framework Appkit

LIBFT	= libft.a

LIBMLX	= libmlx.a

LIBS	= -L./lib/libft -lft -L./lib/mlx -lmlx

all : $(NAME)

$(LIBFT):
	$(MAKE) -C lib/libft

$(LIBMLX):
	$(MAKE) -C lib/mlx

$(NAME)	: $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) -o $(NAME) $(OBJ) $(HEADER) $(CFLAG) $(LIBS) $(MLX)

bonus	: $(OBJ_BONUS) $(LIBFT) $(LIBMLX)
	$(CC) -o $(NAME) $(OBJ_BONUS) $(HEADER_BONUS) $(CFLAG) $(LIBS) $(MLX)

clean :
	$(MAKE) -C lib/libft clean
	$(MAKE) -C lib/mlx clean
	$(RM) $(RMFLAG) $(OBJ_PATH) $(OBJ_BONUS_PATH)

fclean : clean
	$(MAKE) -C lib/libft fclean
	$(RM) $(NAME)

re : fclean all

rebonus : fclean bonus
 .PHONY : all clean fclean re
