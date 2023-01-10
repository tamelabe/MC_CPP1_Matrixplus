CC = gcc
FLAGS = -Wall -Wextra -Werror -lstdc++ -std=c++17
#CFLAGS = -Wall -Werror -Wextra

#LIB_NAME = s21_matrix

#SRCS=$(wildcard s21_*.cpp)

#OBJS=$(SRCS:.c=.o)

all: #$(LIB_NAME).a clean
	@$(CC) $(FLAGS) testing.cpp testing.hpp -o test && ./test

#%.o: %.c
#	$(CC) $(FLAGS) -c $< -o $@
#
#$(LIB_NAME).a: $(OBJS)
#	ar rc $(LIB_NAME).a $^
#	ranlib $(LIB_NAME).a
#	rm -rf *.o

clean:

	rm -rf *.o #test *.a