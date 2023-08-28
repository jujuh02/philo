# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 12:59:57 by juhaamid          #+#    #+#              #
#    Updated: 2023/08/28 12:57:53 by juhaamid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
		utils.c \
		setup.c \
		routine.c \
		utils2.c

OBJS =  ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread  -g3

GREEN = \033[0;32m


all: $(NAME)

$(NAME): ${OBJS}
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "$(GREEN) it compiled!!!$(\033[0m)" 

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all