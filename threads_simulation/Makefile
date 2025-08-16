# Variables
CC = gcc
CFLAGS = -Iincludes -Wall -Wextra -Werror
CFLAGS += -g -pthread -Ofast
LDFLAGS = -Lincludes/mlx -lmlx -lXext -lX11 -lm -lz
CFLAGS += -Iincludes
NAME = simulation
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: mlx $(NAME)

# Rules
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

# Build mlx library
mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./includes/mlx; \
	make -C ./includes/mlx

# Clean rule
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf includes/mlx

re: fclean $(NAME)

run: all
	time ./$(NAME) 6

.PHONY: clean fclean re run all mlx