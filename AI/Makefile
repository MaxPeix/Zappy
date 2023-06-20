##
## EPITECH PROJECT, 2023
## AI
## File description:
## Makefile
##

NAME = zappy_ai

VENV = venv

install:
	python3 -m venv $(VENV)

activate:
	. $(VENV)/bin/activate

requirements: install activate
	./$(VENV)/bin/pip install -r requirement.txt

$(NAME): requirements
	chmod +x $(NAME)

all: $(NAME)

clean:
	rm -rf $(VENV)
	rm -rf __pycache__

re: clean all

.PHONY: install requirements activate $(NAME) all clean re run
