# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 01:18:30 by escura            #+#    #+#              #
#    Updated: 2024/10/07 14:35:26 by escura           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAME_BONUS = cub3d_bonus

all: mlx
	make -j$(nproc) -C mandatory

mlx:
	make mlx -C mandatory
	make mlx -C bonus

run: all
	./$(NAME) map.cub

map:
	make map -C bonus

runb: bonus
	./$(NAME_BONUS) map.cub

bonus: mlx
	make -j$(nproc) -C bonus

clean:
	@make -C mandatory clean > /dev/null
	@make -C bonus clean > /dev/null
	@echo "Cleaning up..."

fclean:
	@make -C mandatory fclean > /dev/null
	@make -C bonus fclean > /dev/null
	rm -rf ./bonus/includes/mlx
	rm -rf ./mandatory/includes/mlx
	@echo "FCleaning up..."

v: bonus
	valgrind --leak-check=full ./$(NAME_BONUS) map.cub

vs: bonus
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME_BONUS) map.cub

re: fclean all

.PHONY: all clean fclean re bonus v vs
