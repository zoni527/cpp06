# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 12:04:28 by jvarila           #+#    #+#              #
#    Updated: 2025/09/09 15:39:21 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= intern_to_the_resque

CXX			:= c++
CXX_FLAGS	:= -Wall -Wextra -Werror -std=c++20
DEBUG_FLAGS	:= -g
# ---------------------------------------------------------------------------- #
INC_DIR		:= ./inc
HEADERS		:= $(INC_DIR)/Bureaucrat.hpp
# ---------------------------------------------------------------------------- #
SRC_DIR	:=	./src
OBJ_DIR	:=	./obj
# ---------------------------------------------------------------------------- #
SRC :=	$(SRC_DIR)/Bureaucrat.cpp				\
		$(SRC_DIR)/AForm.cpp					\
		$(SRC_DIR)/ShrubberyCreationForm.cpp	\
		$(SRC_DIR)/RobotomyRequestForm.cpp		\
		$(SRC_DIR)/PresidentialPardonForm.cpp	\
		$(SRC_DIR)/Intern.cpp					\
		$(SRC_DIR)/main.cpp
# ---------------------------------------------------------------------------- #
OBJ :=	$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

.SECONDARY: $(OBJ)
# ---------------------------------------------------------------------------- #
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -c $< -o $@
# ---------------------------------------------------------------------------- #
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
# ---------------------------------------------------------------------------- #
debug: CXX_FLAGS += $(DEBUG_FLAGS)
debug: fclean all
# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re debug
# ---------------------------------------------------------------------------- #
