# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 12:59:57 by juhaamid          #+#    #+#              #
#    Updated: 2023/08/21 13:04:23 by juhaamid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
	utils.c \
	setup.c

OBJS =  ${SRCS:.c=.o}

CC = cc

CFLGS = -Wall -Werror -Wextra -lpthread

GREEN = \033[0;32m


all: $(NAME)

$(NAME): ${OBJS}
		$(CC) $(CFLGS) $(OBJS) -o $(NAME)
		@echo "$(GREEN) it compiled!!!$(\033[0m)" 


clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all