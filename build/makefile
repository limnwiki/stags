SRC = ../src/main.cpp
NAME = stags
FLAGS = -o $(NAME) -I ../include/

debug:
	g++ $(SRC) $(FLAGS) -Wall -Wextra -pedantic
	./$(NAME)
	
release:
	g++ $(SRC) $(FLAGS) -O2 -s

install:
	make release
	sudo mv $(NAME) /usr/bin/