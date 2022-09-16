# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 15:59:41 by pdal-mol          #+#    #+#              #
#    Updated: 2022/09/15 16:35:35 by pdal-mol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES =	main.c \
			check_input.c \
			utils.c \
			philo.c \

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