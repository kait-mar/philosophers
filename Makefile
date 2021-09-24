# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 17:15:38 by molabhai          #+#    #+#              #
#    Updated: 2021/07/07 15:47:25 by kait-mar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME= philo

CC= gcc -pthread

FLAGS= -Wall -Wextra -Werror -fsanitize=adress

SRCS=  main.c parse.c philo_utils.c time.c create_thread.c ft_atoi.c

OBJ = $(SRCS:.c=.o)

HEADERS= philo.h

DELETEOBJ= rm -rf *.o

DELETENAME= rm -rf $(NAME)


all: $(NAME)
$(NAME):
	$(CC) $(SRCS)  -o philo
clean:
	$(DELETEOBJ) $(DELETENAME)

fclean : clean
	rm -rf $(NAME)

re: clean all
