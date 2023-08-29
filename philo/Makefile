# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 12:59:57 by juhaamid          #+#    #+#              #
#    Updated: 2023/08/29 17:07:05 by juhaamid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
		utils.c \
		setup.c \
		eat.c \
		routine.c \
		parsing.c \
		utils2.c

OBJS =  ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread 

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