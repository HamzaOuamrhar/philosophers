# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/09 23:13:14 by houamrha          #+#    #+#              #
#    Updated: 2024/03/22 16:38:12 by houamrha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc  -Wall -Wextra -Werror -g -fsanitize=address
SRC = philo_bonus.c ft_atoi_bonus.c ft_strcmp_bonus.c
OBJ = $(SRC:.c=.o)
NAME = philo_bonus

all  : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o : %.c philo_bonus.h
	$(CC) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean
