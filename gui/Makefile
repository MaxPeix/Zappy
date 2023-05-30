##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Gautier BONHUR
##

NAME			=	zappy_gui

SRC_MAIN		= src/main.c

SRC				=	src/core.c

SRC_TESTS = tests/tests_main.c

OBJ				=			$(SRC:.c=.o)

OBJ_MAIN		=			$(SRC_MAIN:.c=.o)

CFLAGS 			= 			-I./includes

CRITERION		= 			--coverage -lcriterion

all: 			$(NAME)

$(NAME):		$(OBJ) $(OBJ_MAIN)
	g++ -o $(NAME) $(OBJ) $(OBJ_MAIN) $(LDFLAGS)

tests_run: $(OBJ)
	make re
	g++ -o unit_tests $(SRC) $(SRC_TESTS) $(CFLAGS) $(CRITERION)
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

re:	$(NAME)

.PHONY: all $(NAME) fclean tests_run clean re make
