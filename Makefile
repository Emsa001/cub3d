# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 01:18:30 by escura            #+#    #+#              #
#    Updated: 2024/06/18 19:23:17 by escura           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)

# Compiler and Flags
CC = cc
CPP = clang++
# CFLAGS = -Wall -Wextra -Werror
CPPFLAGS += -g -fPIE
CPPFLAGS += -I$(LIBFT_DIR) -Iincludes
LDFLAGS += -L./includes/mlx -lmlx -lXext -lX11 -lm -lz 

DEBUG 		= 0
FSANITIZE 	= 0

ifeq ($(DEBUG), 1)
    CPPFLAGS += -DDEBUG=1
endif

ifeq ($(FSANITIZE), 1)
    CPPFLAGS += -fsanitize=address -fno-omit-frame-pointer
endif

LIBFT_DIR = ./includes/libft/
LIBFT = $(LIBFT_DIR)/libft.a
LDLIBS = -L$(LIBFT_DIR) -lft

OBJ_DIR = .obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_TEST = $(filter-out $(OBJ_DIR)/main.o,$(OBJ))

all: $(NAME) run

run: all
	./$(NAME) map.cub

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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
	git clone https://github.com/42Paris/minilibx-linux.git ./includes/mlx
	
# ===== Tests =====
TEST_DIR = tests
TEST_REPO = git@github.com:triedel42/minishell-tests
TEST = $(TEST_DIR)/test
LIBGTEST_DIR = googletest
LIBGTEST = $(LIBGTEST_DIR)/build/lib/libgtest.a
CXX = c++
CXXFLAGS = -std=c++14
CXXFLAGS += -I$(LIBGTEST_DIR)/googletest/include
CXXFLAGS += -Wno-write-strings
LDLIBS += -L$(LIBGTEST_DIR)/build/lib

t: $(TEST)
	./$(TEST)

$(TEST): $(TEST_DIR) $(OBJ_TEST) $(LIBGTEST)
	$(CXX) -o $@ $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(wildcard tests/*.cc) $(OBJ_TEST) $(LDLIBS) -lgtest

$(TEST_DIR):
	git clone $(TEST_REPO) $(TEST_DIR)

$(LIBGTEST_DIR):
	git clone --depth=1 https://github.com/google/googletest $@

$(LIBGTEST): $(LIBGTEST_DIR)
	cd $< && mkdir -p build && cd build && cmake ..
	make -j$(shell nproc) -C$(LIBGTEST_DIR)/build

.PHONY: all clean fclean re run t v
