# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 07:36:19 by eaqrabaw          #+#    #+#              #
#    Updated: 2025/01/28 07:38:31 by eaqrabaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = 	main \
		utils \
		philo_ops
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = includes/philosophers.h
FULL_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c, $(SRCS)))
OBJS = $(addprefix $(OBJ_DIR),$(addsuffix .o, $(SRCS)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean ree