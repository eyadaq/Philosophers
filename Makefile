# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 07:36:19 by eaqrabaw          #+#    #+#              #
#    Updated: 2025/05/08 11:44:31 by eaqrabaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS = -lpthread
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
HEADER = philosophers.h
SRCS 		= main \
		  	  routine \
		  	  initiate_input \
		  	  input_validation \
		  	  initiate_philos \
			  free_utils \
			  monitor
INCLUDES = $(addprefix $(INC_DIR)/, $(HEADER))
SOURCE = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRCS)))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRCS)))
GREEN   	= \033[0;32m
RED    		= \033[0;31m
RESET   	= \033[0m
ARROW   	= ✔
				
all : $(NAME)

$(NAME) : $(OBJECTS)
	@echo "$(GREEN)Creating The Executable File...$(RESET)"
	@$(CC) $(OBJECTS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Done...$(ARROW)$(RESET) "

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDES) | $(OBJ_DIR) 
	@echo "$(GREEN)Creating The OBJ Files...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@  
	@echo "$(GREEN)Done..$(ARROW)$(RESET)"

$(OBJ_DIR) :
	@echo "$(GREEN)Making the OBJ Directory $(RESET)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)Done..$(ARROW) $(RESET)"

clean :
	@echo "$(RED)Cleaning the object files $(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Done...$(ARROW) $(RESET)"
	
fclean : clean
	@echo "$(RED)Cleaning the executable $(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)Done...$(ARROW) $(RESET)"

re : fclean all

.PHONY: all clean fclean re