# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 07:36:19 by eaqrabaw          #+#    #+#              #
#    Updated: 2025/01/21 08:02:07 by eaqrabaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers
CC = CC
CFLAGS = -Wall -Werror Wextra
SRCS = main
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = includes/philosophers.h
FULL_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c, $(SRCS)))
OBJS = $(addprefix $(OBJ_DIR),$(addsuffix .o, $(SRCS)))

$(NAME) : all

all : $(OBJS)

$(OBJ_DIR)%.o : %.c $(HEADER) | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all 

.PHONY : all clean fclean re