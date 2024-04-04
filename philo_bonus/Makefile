# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/09 23:13:14 by houamrha          #+#    #+#              #
#    Updated: 2024/04/04 12:03:33 by houamrha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc  -Wall -Wextra -Werror
SRC = philo_bonus.c utils_bonus.c ft_atoi_bonus.c ft_strcmp_bonus.c one_philo_bonus.c utils2_bonus.c utils3_bonus.c ft_itoa_bonus.c ft_strjoin_bonus.c
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
