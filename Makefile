# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrean <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 00:40:11 by adrean            #+#    #+#              #
#    Updated: 2018/10/05 14:09:37 by adrean           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = b_ls
SRC = *.c
FLAGS = -Wall -g -fsanitize=address

$(NAME):
	gcc $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
