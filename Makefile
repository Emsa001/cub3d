# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 01:18:30 by escura            #+#    #+#              #
#    Updated: 2024/09/26 13:05:42 by btvildia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAME_BONUS = cub3d_bonus

all: 
#	make mlx -C mandatory
	make -j$(nproc) -C mandatory

run: all
	./$(NAME) map.cub

map:
	make map -C bonus

runb: bonus
	./$(NAME_BONUS) map.cub

bonus:
	make mlx -C bonus
	make -j$(nproc) -C bonus

clean:
	@make -C mandatory clean > /dev/null
	@make -C bonus clean > /dev/null
	@echo "Cleaning up..."

fclean:
	@make -C mandatory fclean > /dev/null
	@make -C bonus fclean > /dev/null
	@echo "FCleaning up..."

v: bonus
	valgrind --leak-check=full ./$(NAME_BONUS) map.cub

vs: bonus
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME_BONUS) map.cub

re: fclean all

.PHONY: all clean fclean re bonus v vs
