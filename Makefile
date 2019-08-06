NAME = avm

FLAGS = -std=c++11 -Wall -Wextra -Werror

OBJ_DIR = ./obj/
SRC_DIR = ./src/
INCDIR = ./inc/

SRC =	main.cpp \
		AvmExceptions.cpp \
        Lexer.cpp \
        Operand.cpp \
        OperandsFactory.cpp \
        Parser.cpp \
        Stack.cpp \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
HDRS = -I $(INCDIR)

all: $(NAME)

$(NAME): $(OBJ)
		@clang++ $(FLAGS) $(OBJ) -o $(NAME) $(HDRS)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
				@clang++ -c $< -o $@ $(FLAGS) $(HDRS)

clean:
	@rm -f $(OBJ)

fclean: clean
		@rm -f $(NAME)
		@rm -rf $(OBJ_DIR)

re: fclean all