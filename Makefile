NAME = pathfinder

INC = inc/header.h

SRCR = mx_algo.c \
	mx_create_arr_words.c \
	mx_create_isls.c \
	mx_fill_bridge.c \
	mx_invalid_file.c \
	mx_print_errors.c \
	mx_print_pathes.c \
	pathfinder_main.c \
	route_tools.c \

SRC = $(addprefix src/, $(SRCR))

OBJR = $(SRCR:.c=.o)

OBJ = $(addprefix obj/, $(OBJR))

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

LIB = libmx/libmx.a

all: 
	@make -C libmx
	@mkdir obj
	@clang $(FLAGS) -c $(SRC)
	@mv $(OBJR) obj
	@clang $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

install: all
	@cp $(LIB) .

uninstall:
	@rm -rf ./libmx.a

clean: uninstall
	@rm -rf $(NAME)
	@rm -rf ./obj
	@make clean -C libmx

reinstall: clean install
