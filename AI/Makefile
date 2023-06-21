##
## EPITECH PROJECT, 2023
## AI
## File description:
## Makefile
##

NAME = zappy_ai

$(NAME): requirements build

build: requirements
	pip install nuitka
	python -m nuitka --standalone --standalone --onefile --remove-output main.py --output-filename=$(NAME)


requirements:
	pip install -r requirement.txt

all: build

clean:
	rm -rf __pycache__

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: $(NAME) build requirements all clean fclean re run
