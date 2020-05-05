NAME = computor

OS := $(shell uname)
ifeq ($(OS),Darwin)
  CXX=clang++
  INCLUDE_AND_LIBS = -I $(HOME)/.brew/Cellar/boost/1.67.0_1/include \
					-L $(HOME)/.brew/Cellar/boost/1.67.0_1/lib \
					-I include
  FLAGS = -std=c++11 -Wall -Wextra -Werror \
			-lboost_filesystem  -lboost_system  -lboost_program_options \
			-pthread -lboost_thread-mt -Wno-unused-command-line-argument \
			-Wno-unused-parameter -O2
else
  CXX=g++
  INCLUDE_AND_LIBS = -I /usr/include/boost -L /usr/lib/x86_64-linux-gnu -I include
  FLAGS = -std=c++14 -Wall -Wextra -Werror \
			-lboost_filesystem  -lboost_system -lboost_program_options \
			-pthread -lboost_thread \
			-Wno-unused-parameter -O2
endif

OBJDIR = obj/

SRCDIR = src/

_SRC =	main.cpp \
		CLI.cpp \
		Equitation.cpp \

SRC = $(addprefix $(SRCDIR), $(_SRC))

OBJ = $(addprefix $(OBJDIR),$(_SRC:.cpp=.o))

all: make_dir $(NAME)

make_dir:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) $(INCLUDE_AND_LIBS) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ) $(SRC)
	$(CXX) $(INCLUDE_AND_LIBS) -o $(NAME) $(OBJ) $(FLAGS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
