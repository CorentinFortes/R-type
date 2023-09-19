

NAME = 	client
SRC =	*.cpp
OBJ = $(SRC:.cpp=.o)


all :
	g++ -c $(SRC) -I./include
	g++ -o $(NAME) $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f ./lib/*.so

re :	 fclean all