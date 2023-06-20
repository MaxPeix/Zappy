##
## EPITECH PROJECT, 2023
## AI
## File description:
## Makefile
##

NAME = zappy_ai

$(NAME): requirements build

deps:
	python3 -m venv venv

build: requirements
	./venv/bin/pip install nuitka
	python -m nuitka --standalone --standalone --onefile --remove-output main.py --output-filename=$(NAME)

activate:
	. venv/bin/activate

requirements: deps activate
	./venv/bin/pip install -r requirement.txt

all: build

clean:
	rm -rf venv
	rm -rf __pycache__

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: $(NAME) install build requirements activate all clean fclean re run
