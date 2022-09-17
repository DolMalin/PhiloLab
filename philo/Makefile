# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 15:59:41 by pdal-mol          #+#    #+#              #
#    Updated: 2022/09/16 16:39:20 by pdal-mol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES =	main.c \
			check_input.c \
			utils.c \
			philo.c \
			data.c \
			routine.c

SRC =		${addprefix src/, ${SRC_FILES}}
OBJS = 		${SRC:.c=.o}
NAME = 		philo
HEADERS = 	includes/main.h
CFLAGS = 	-Wall -Wextra -Werror 
# -fsanitize=thread -g3 
CC = 		gcc

%.o: 		%.c ${HEADERS} Makefile 
			${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${NAME} ${OBJS}

re:	fclean all

.PHONY:	all clean fclean re