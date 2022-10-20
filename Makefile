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
SRC 		= fdf.c fdf_parse.c fdf_parse_util.c fdf_util_1.c fdf_util_2.c fdf_proj.c fdf_con_dots.c fdf_keyhook.c fdf_put_panel.c
OBJ 		= $(SRC:.c=.o)
# BONUS_SRC	= ./bonus/fdf_bonus.c ./bonus/fdf_parse_bonus.c ./bonus/fdf_parse_util_bonus.c ./bonus/fdf_util_1_bonus.c ./bonus/fdf_util_2_bonus.c ./bonus/fdf_proj_bonus.c ./bonus/fdf_con_dots_bonus.c ./bonus/fdf_keyhook_bonus.c ./bonus/fdf_put_panel_bonus.c
# BONUS_OBJ	= fdf_bonus.o fdf_parse_bonus.o fdf_parse_util_bonus.o fdf_util_1_bonus.o fdf_util_2_bonus.o fdf_proj_bonus.o fdf_con_dots_bonus.o fdf_keyhook_bonus.o fdf_put_panel_bonus.o
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
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT_DIR)/libft/*.c $(LIBFT_DIR)/ft_printf/*.c $(LIBFT_DIR)/gnl/*.c -lmlx_Linux -lX11 -lXext -L./minilibx-linux -lm
#	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -lft -L$(LIBFT_DIR) $(MLX_FLAGS)

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

# bonus : $(NAME) $(BONUS_SRC)
# 	make WITH_BONUS=1 $(NAME)
