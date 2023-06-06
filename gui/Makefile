##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Gautier BONHUR
##

NAME			=	zappy_gui

SRC_MAIN		= src/main.cpp

SRC				=	src/gui.cpp	\
					src/assets.cpp

SRC_TESTS = tests/tests_main.c

OBJ				=			$(SRC:.cpp=.o)

OBJ_MAIN		=			$(SRC_MAIN:.cpp=.o)

OBJ_TESTS			=			$(SRC_TESTS:.cpp=.o)

CPPFLAGS			=			-Iincludes -Wall -Wextra -Werror -std=c++2a

SFML			=			-lsfml-graphics -lsfml-window -lsfml-system

CRITERION		= 			--coverage -lcriterion

all: 			$(NAME)

$(NAME):		$(OBJ) $(OBJ_MAIN)
	g++ -o $(NAME) $(OBJ) $(OBJ_MAIN) $(CPPFLAGS) $(SFML)

tests_run: $(OBJ)
	make re
	g++ -o unit_tests $(OBJ) $(OBJ_TESTS) $(CRITERION)
	./unit_tests
	rm unit_tests

clean:
	rm -f $(OBJ)
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f unit_tests

fclean:			clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY: all $(NAME) fclean tests_run clean re make
