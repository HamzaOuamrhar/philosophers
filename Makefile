# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/09 23:13:14 by houamrha          #+#    #+#              #
#    Updated: 2024/03/26 15:32:12 by houamrha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc  -Wall -Wextra -Werror -g -fsanitize=thread
SRC = philo.c utils.c ft_atoi.c ft_strcmp.c thread_handler.c one_philo.c utils2.c
OBJ = $(SRC:.c=.o)
NAME = philo

all  : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o : %.c philo.h
	$(CC) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean
