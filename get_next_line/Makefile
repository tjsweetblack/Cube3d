# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joandre <joandre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 10:34:56 by joandre           #+#    #+#              #
#    Updated: 2025/01/16 11:08:06 by joandre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
SRC = get_next_line.c get_next_line_utils.c
CC = cc 
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRC:.c=.o)

all:	$(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I . -c $< -o $@

$(NAME):	$(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all