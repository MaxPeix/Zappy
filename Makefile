##
## EPITECH PROJECT, 2023
## B-YEP-400-BDX-4-1-zappy-max.peixoto
## File description:
## Makefile
##

NAME			=	zappy

NAME_SERVER		=	zappy_server

NAME_GUI		=	zappy_gui

NAME_AI			=	zappy_ai

all :			$(NAME)

$(NAME) :
				make -C server
				make -C gui
				make -C ai
				cp server/zappy_server .
				cp gui/zappy_gui .
				cp ai/zappy_ai .

$(NAME_SERVER) :
				make -C server
				cp server/zappy_server .

$(NAME_GUI) :
				make -C gui
				cp gui/zappy_gui .

$(NAME_AI) :
				make -C ai
				cp ai/zappy_ai .

clean :
				make clean -C server
				make clean -C gui
				make clean -C ai

fclean :		clean
				make fclean -C server
				make fclean -C gui
				rm -f			$(NAME)
				rm -f			$(NAME_SERVER)
				rm -f			$(NAME_GUI)
				rm -f			$(NAME_AI)
				make fclean -C ai

re :			fclean all

.PHONY :		all clean fclean re
