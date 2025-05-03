# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joandre <joandre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 10:21:32 by joandre           #+#    #+#              #
#    Updated: 2025/04/16 20:04:47 by joandre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cube3d
CFLAGS = -Wall -Werror -Wextra -g
CC = cc
CORE_DIR = ./core
MINILBX_DIR = ./mlx
MINILIB_LIB = libmlx.a
#MAIN = main.cexit
COMMON_SRC = $(wildcard $(CORE_DIR)/*.c) # Expands to all .c files in directories
OBJ = $(COMMON_SRC:.c=.o) #$(MAIN:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MINILBX_DIR)
	$(CC) $(CFLAGS) $(OBJ) -L$(MINILBX_DIR) -lmlx -lX11 -lXext -lm -o $(NAME)
	@echo "Program is ready!!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(MINILBX_DIR)
	@rm -f $(OBJ)
	@echo "Object files have been cleaned successfully"

fclean: clean
	@rm -f $(NAME)
	@echo "Objects and executables removed"

re: fclean all
