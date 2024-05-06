# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/08 13:40:39 by janhan            #+#    #+#              #
#    Updated: 2024/01/11 15:40:43 by janhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
HEAD = libft.h
SRCS =				ft_isprint.c				\
					ft_isalpha.c				\
					ft_isdigit.c				\
					ft_isalnum.c				\
					ft_isascii.c				\
					ft_strlen.c					\
					ft_memset.c					\
					ft_bzero.c					\
					ft_memcpy.c					\
					ft_memmove.c				\
					ft_strlcpy.c				\
					ft_strlcat.c				\
					ft_toupper.c				\
					ft_tolower.c				\
					ft_strchr.c					\
					ft_strrchr.c				\
					ft_strncmp.c				\
					ft_memchr.c					\
					ft_memcmp.c					\
					ft_strnstr.c				\
					ft_atoi.c					\
					ft_calloc.c					\
					ft_strdup.c					\
					ft_substr.c					\
					ft_strjoin.c				\
					ft_strtrim.c				\
					ft_split.c					\
					ft_itoa.c					\
					ft_strmapi.c				\
					ft_striteri.c				\
					ft_putchar_fd.c				\
					ft_putstr_fd.c				\
					ft_putendl_fd.c				\
					ft_putnbr_fd.c				\
					ft_lstnew.c					\
					ft_lstadd_front.c			\
					ft_lstsize.c				\
					ft_lstlast.c				\
					ft_lstadd_back.c			\
					ft_lstdelone.c				\
					ft_lstclear.c				\
					ft_lstiter.c				\
					ft_lstmap.c					\
					ft_printf.c 				\
					ft_print_char.c 			\
					ft_print_str.c 				\
					ft_print_di.c 				\
					ft_print_hex.c 				\
					ft_print_u.c 				\
					ft_print_address.c			\
					ft_strend_cmp.c				\
					ft_chartable_linecount.c	\
					ft_free_chartable.c


OBJS = $(SRCS:.c=.o)

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
PURPLE='\033[35m'
BLUE='\033[34m'
DELETELINE='\033[K;

all : $(NAME)

$(NAME): $(OBJS)
	@echo $(CURSIVE)$(YELLOW) "        - Making $(NAME) -" $(NONE)
	@ar cr $@ $^
	@echo $(CURSIVE)$(YELLOW) "       - Compiling $(NAME) -" $(NONE)
	@echo $(GREEN)"             - Complete -"$(NONE)

%.o: %.c
	@echo $(CURSIVE)$(YELLOW) "      - Making object files -" $(NONE)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEAD)

clean :
	@rm -fr $(OBJS)
	@echo $(CURSIVE)$(BLUE) "     - clean $(NAME) OBJ files -" $(NONE)

fclean :
	@rm -fr $(OBJS)
	@rm -fr $(NAME)
	@echo $(CURSIVE)$(PURPLE)"      - clean $(NAME) file -" $(NONE)

re :
	make fclean
	make all

.PHONY: all make clean fclean re
