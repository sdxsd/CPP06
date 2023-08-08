NAME = serializer
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++11
FILES = \
		Serialization.cpp \
		main.cpp
OFILES = $(FILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(FLAGS) $(OFILES) -o $(NAME)

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "COMPILED:" $<

clean:
	rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
