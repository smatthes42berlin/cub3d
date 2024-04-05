SHELL:=/bin/bash
CFLAGS = -g -O3 -Wall -Wextra -Werror $(INCLUDEFLAGS)
LDFLAGS = -Lmlx -lmlx -lXext -lX11 -lm

# CFLAGS = -Wall -Wextra -Werror -fsanitize=leak  $(INCLUDEFLAGS) 
# CFLAGS = -Wall -Wextra -Werror fsanitize=addressmak  $(INCLUDEFLAGS) 
NAME = cub3D
LINK= cc
CC = cc

NAMELIBFT = libft.a
FOLDERLIBFT = ./libft/
PATHLIBFT = $(FOLDERLIBFT)$(NAMELIBFT)

INCLUDEPATH = ./include/ ./libft/include/ ./libft/ ./mlx/
INCLUDEFLAGS = $(patsubst %,-I% ,$(INCLUDEPATH))
# if you created a new subfolder in the source dir, you gotta list it here as well, so c-files are found
SUBFOLDERSRC = . /error /parse_map /raycast
BASEPATHSRC = ./src/
PATHSRC = $(patsubst %,$(BASEPATHSRC)%,$(SUBFOLDERSRC))
PATHBUILD = build/
PATHOBJ = build/

# create build folder
$(shell if [ ! -d $(PATHBUILD) ]; then \
    mkdir -p $(PATHBUILD); \
fi)

# specifies the path, where the compiler will look for files (e.g. *.c, *.h files)
# that way, you dont have to specify full filepath when listing source files below
VPATH = $(PATHSRC) $(INCLUDEPATH)

# list all filenames (without path) here
SRC = 	main.c \
		throw_error.c \
		get_failed_func_str.c \
		parse_main.c \
		init_parse_state.c \
		parse_util_1.c \
		parse_util_2.c \
		handle_ceil.c \
		handle_ea.c \
		handle_floor.c \
		handle_map_start.c \
		handle_newline.c \
		handle_no.c \
		handle_so.c \
		handle_unknown.c \
		handle_we.c \
		raycast.c



OBJFNAME = $(SRC:.c=.o)
OBJ = $(patsubst %,$(PATHOBJ)%,$(OBJFNAME))

.PHONY: all clean fclean re fcleanall reall leaks

all: $(NAME)

$(NAME): $(PATHLIBFT) $(OBJ)
	$(LINK) $(CFLAGS) -o $(NAME) $(OBJ) $(PATHLIBFT) $(LDFLAGS)

$(PATHOBJ)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PATHLIBFT): 
	make -C $(FOLDERLIBFT)

clean:
	make -C $(FOLDERLIBFT) clean
	$(RM) $(OBJ)

fcleanall: clean
	make -C libft fclean
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

leaks:
	@make
	@valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./test_maps/1.cub

reall: fcleanall all

re: fclean all

.PRECIOUS: $(PATHOBJ)%.o
