# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 14:06:07 by escura            #+#    #+#              #
#    Updated: 2024/05/16 14:15:47 by escura           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra #-Werror
CFLAGS += -Iincludes
# CFLAGS += -fsanitize=address -fno-omit-frame-pointer

MLX_DIR = $(INCLUDES_DIR)/mlx_linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)

OBJ_DIR = .obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_DIR = ./includes/libft/
LIBFT = $(LIBFT_DIR)/libft.a
LDLIBS = -L$(LIBFT_DIR) -lft

CFLAGS += -I$(LIBFT_DIR) -Iincludes -I$(MLX_DIR)

all: $(NAME)
	./$(NAME) 10.12.9.3 escura

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $(NAME) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR) 

re: fclean all
