# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moguy <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/22 01:19:35 by moguy             #+#    #+#              #
#    Updated: 2020/03/04 14:08:00 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF = \033[0m
GRA = \033[1m
SOU = \033[4m
BLI = \033[5m
BLA = \033[30m
RED = \033[31m
GRE = \033[32m
YEL = \033[33m
BLU = \033[34m
PUR = \033[35m
CYA = \033[36m
WHI = \033[37m
ORG = \033[1;31m

CC=gcc
CFLAGS = -Wall -Werror -Wextra

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g3 -fsanitize=address
endif

NAME=wolf3d

SRCS_PATH=srcs/
SRCS_NAME=deal.c\
		  fill_pixel.c\
		  get_map.c\
		  init.c\
		  key_action.c\
		  main.c\
		  mini_map.c\
		  raycasting.c\
		  sample_color.c\
		  singleton.c\
		  tab_del.c\
		  threader.c

INC_PATH=includes/
INC_NAME=wolf3d.h

MLX_PATH=/usr/local/lib/
MLX_NAME=libmlx.a

LIB_PATH=libft/
LIB_NAME=libft.a

OBJS=$(SRCS:.c=.o)

SRCS=$(addprefix $(SRCS_PATH), $(SRCS_NAME))

INC=$(addprefix $(INC_PATH), $(INC_NAME))

MLX=$(addprefix $(MLX_PATH), $(MLX_NAME))

LIB=$(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all clean fclean re

all : $(LIB) $(NAME)

$(LIB) : $(LIB_PATH)
	@make -C $(LIB_PATH)

$(NAME) : $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) -I$(INC_PATH) $(OBJS) \
		-framework OpenGL -framework Appkit -lpthread $(LIB) $(MLX)
	@echo "$(GRE)Done !$(DEF)"

$(SRCS_PATH)%.o : $(SRCS_PATH)%.c $(INC)
	$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -o $@ -c $<

clean :
	@rm -rf $(OBJS)
	@make -C $(LIB_PATH) clean

fclean : clean
	@rm -rf $(NAME)
	@make -C $(LIB_PATH) fclean

re : fclean all
