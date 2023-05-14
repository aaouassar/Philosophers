# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 13:18:12 by aaouassa          #+#    #+#              #
#    Updated: 2023/04/17 00:35:25 by aaouassa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC = Philosophers.c threads.c creat.c help.c time.c

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	 gcc  $(OBJS) -o $(NAME)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
	
re : fclean all