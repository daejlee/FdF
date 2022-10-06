# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 15:07:02 by daejlee           #+#    #+#              #
#    Updated: 2022/09/09 15:07:02 by daejlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= fdf
CFLAGS 		= -Wall -Wextra -Werror
CC 			= cc
SRC 		= main.c fdf_parse.c fdf_util_1.c fdf_proj.c fdf_con_dots.c
OBJ 		= $(SRC:.c=.o)
LIBFT 		= ./libft_garage/libft.a
LIBFT_DIR	= ./libft_garage
MLX_DIR		= ./mlx
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework Appkit

ifdef WITH_BONUS
	OBJ_FILES = $(BONUS_OBJ)
	SRC_FILES = $(BONUS_SRC)
else
	OBJ_FILES = $(OBJ)
	SRC_FILES = $(SRC)
endif

all : $(NAME)

$(NAME) : $(OBJ_FILES) $(LIBFT)
#	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -lft -L$(LIBFT_DIR) $(MLX_FLAGS)
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT_DIR)/libft/*.c $(LIBFT_DIR)/ft_printf/*.c $(LIBFT_DIR)/gnl/*.c -lmlx_Linux -lX11 -lXext -L./minilibx-linux -lm
#	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT_DIR)/libft/*.c $(LIBFT_DIR)/ft_printf/*.c $(LIBFT_DIR)/gnl/*.c $(MLX_FLAGS)

$(OBJ_FILES) : $(SRC_FILES)
	$(CC) $(CFLAGS) -c $(SRC_FILES)

$(LIBFT) :
	cd $(LIBFT_DIR); $(MAKE)

clean :
	rm -f $(OBJ_FILES) $(BONUS_OBJ)
	make -C libft_garage/ clean

fclean :
	rm -f $(OBJ_FILES) $(BONUS_OBJ) $(NAME)
	make -C libft_garage/ fclean

re :
	$(MAKE) fclean
	$(MAKE) all
