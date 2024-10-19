# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/19 10:37:58 by nkiampav          #+#    #+#              #
#    Updated: 2024/10/19 10:38:00 by nkiampav         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

SRCS = 	philo.c \
		init.c \
		philosopher.c \
		utils.c \

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