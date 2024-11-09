# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/19 10:37:58 by nkiampav          #+#    #+#              #
#    Updated: 2024/11/09 12:01:42 by nkiampav         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

SRCS = 	main.c \
		parse_arguments.c \
		init.c \
		monitor.c \
		time.c \
		utils.c \
		actions.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
