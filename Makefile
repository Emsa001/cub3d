# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 01:18:30 by escura            #+#    #+#              #
#    Updated: 2024/07/21 18:03:12 by btvildia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAME_BONUS = cub3d_bonus

all: 
	make -j$(nproc) -C mandatory

run: all
	./$(NAME) map.cub

runb: bonus
	./$(NAME_BONUS) bonus2.cub

bonus:
	make -j$(nproc) -C bonus

clean:
	@make -C mandatory clean > /dev/null
	@make -C bonus clean > /dev/null
	@echo "Cleaning up..."

fclean:
	@make -C mandatory fclean > /dev/null
	@make -C bonus fclean > /dev/null
	@echo "FCleaning up..."

re: fclean all

.PHONY: all clean fclean re bonus
