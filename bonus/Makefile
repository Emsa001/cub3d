# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 01:18:30 by escura            #+#    #+#              #
#    Updated: 2024/09/19 17:44:34 by btvildia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../cub3d_bonus

INCLUDES_DIR = includes
INCLUDES = $(wildcard $(INCLUDES_DIR)/*.h) $(wildcard $(INCLUDES_DIR)/*/*.h)

FT_ASYNC = $(INCLUDES_DIR)/ft_async/src

SRC_DIR = src
SRC = $(filter-out $(wildcard $(SRC_DIR)/_*), $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)) $(FT_ASYNC)/manager.c $(FT_ASYNC)/new_async.c $(FT_ASYNC)/start_async.c $(FT_ASYNC)/stop_async.c


# Compiler and Flags
CC = cc

CFLAGS = -g -O3
# CFLAGS += -fsanitize=thread
# CFLAGS += -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror

CFLAGS += -I$(LIBFT_DIR) -I$(INCLUDES_DIR)
LDFLAGS += -L./$(INCLUDES_DIR)/mlx -lmlx -lXext -lX11 -lm -lz

DEBUG 		= 0

ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG=1
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
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) $(LIBFT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) DEBUG=$(DEBUG)
	
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
	valgrind --leak-check=full $(NAME) ../map.cub

mlx:
	@if [ ! -d "$(INCLUDES_DIR)/mlx" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git ./$(INCLUDES_DIR)/mlx; \
	fi
	
.PHONY: all clean fclean re run v

