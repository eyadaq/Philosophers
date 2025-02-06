# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 07:36:19 by eaqrabaw          #+#    #+#              #
#    Updated: 2025/02/06 07:59:51 by eaqrabaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = 	main \
		handle_input\
		initialization\
		routine\
		routine_utils
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = includes/philosophers.h
GREEN   	= \033[0;32m
RED    		= \033[0;31m
RESET   	= \033[0m
ARROW   	= ✔
FULL_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c, $(SRCS)))
OBJS = $(addprefix $(OBJ_DIR),$(addsuffix .o, $(SRCS)))
LDFLAGS = -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Making $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "$(GREEN)Done $(ARROW)$(RESET)"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJ_DIR)
	@echo "$(GREEN)Generating $@ $(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Done $(ARROW)$(RESET)"

$(OBJ_DIR):
	@echo "$(GREEN)Creating OBJ_DIR$(RESET)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)Done $(ARROW)$(RESET)"

clean:
	@echo "$(RED)Deleting $(objDir)...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Done $(ARROW)$(RESET)"

fclean: clean
	@echo "$(RED)Deleting $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)Done $(ARROW)$(RESET)"

re: fclean all

.PHONY: all clean fclean ree