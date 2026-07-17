# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:37:43 by epinaud           #+#    #+#              #
#    Updated: 2026/07/17 11:43:56 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


EXE = ReversePolishNotation

CC = c++

CFLAGS = -std=c++98 -Wall -Wextra -Werror

INCLUDES = -I. -Iincludes/

OBJ_DIR = .obj

SRCS = main.cpp RPN.cpp

$(OBJ_DIR)/%.o : %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

all: $(OBJ_DIR) $(EXE)

$(EXE) :
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

ReversePolishNotation: $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

.obj:
	@mkdir -p .obj

clean:
	@rm -f $(EXE)

fclean:  clean
	@rm -rf $(OBJ_DIR)

re: fclean $(OBJ_DIR) $(EXE)

.PHONY:  all clean fclean re