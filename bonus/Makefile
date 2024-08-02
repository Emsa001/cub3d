# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 01:18:30 by escura            #+#    #+#              #
#    Updated: 2024/08/02 21:49:52 by escura           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d_bonus

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)

INCLUDES_DIR = includes

# Compiler and Flags
CC = cc

CFLAGS = -g -O3
# CFLAGS = -Wall -Wextra -Werror

CFLAGS += -I$(LIBFT_DIR) -I$(INCLUDES_DIR)
LDFLAGS += -L./$(INCLUDES_DIR)/mlx -lmlx -lXext -lX11 -lm -lz 

DEBUG 		= 0
FSANITIZE 	= 1

ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG=1
endif

ifeq ($(FSANITIZE), 1)
    CFLAGS += -fsanitize=address -fno-omit-frame-pointer
endif

LIBFT_DIR = ./$(INCLUDES_DIR)/libft/
LIBFT = $(LIBFT_DIR)/libft.a
LDLIBS = -L$(LIBFT_DIR) -lft

OBJ_DIR = .obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

run: $(NAME)
	./$(NAME) map.cub

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS)$(OBJ) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) DEBUG=$(DEBUG) FSANITIZE=$(FSANITIZE)
	
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) 
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean
	$(MAKE) all

# ===== Utils =====
v: $(NAME)
	valgrind --leak-check=full ./$(NAME) map.cub

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./$(INCLUDES_DIR)/mlx
	
.PHONY: all clean fclean re run v
