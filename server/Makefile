##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Gautier BONHUR
##

NAME			=	zappy_server

SRC_MAIN		= src/main.c

SRC				=	src/core.c \
					src/init_server.c \
					src/ressources.c \
					src/distribute_ressource_one.c \
					src/distribute_ressource_two.c \
					src/errors/handle_error.c \
					src/clients/client_gestion.c \
					src/clients/protocol_start.c \
					src/clients/lib.c \
					src/clients/init.c \
					src/commands/handle_command.c \
					src/commands/handle_command_lib.c \
					src/commands/graphic_command.c


SRC_TESTS = tests/tests_main.c

OBJ				=			$(SRC:.c=.o)

OBJ_MAIN		=			$(SRC_MAIN:.c=.o)

CFLAGS 			= 			-I./includes

CRITERION		= 			--coverage -lcriterion

all: 			$(NAME)

$(NAME):		$(OBJ) $(OBJ_MAIN)
	gcc -o $(NAME) $(OBJ) $(OBJ_MAIN) $(LDFLAGS)

tests_run: $(OBJ)
	make re
	gcc -o unit_tests $(SRC) $(SRC_TESTS) $(CFLAGS) $(CRITERION)
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
