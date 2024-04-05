SHELL:=/bin/bash
CFLAGS = -Wall -Wextra -Werror $(INCLUDEFLAGS)
# CFLAGS = -Wall -Wextra -Werror -fsanitize=leak  $(INCLUDEFLAGS) 
# CFLAGS = -Wall -Wextra -Werror fsanitize=addressmak  $(INCLUDEFLAGS) 
NAME = cub3D
LINK= cc
CC = cc

NAMELIBFT = libft.a
FOLDERLIBFT = ./libft/
PATHLIBFT = $(FOLDERLIBFT)$(NAMELIBFT)

INCLUDEPATH = ./include/ ./libft/include/ ./libft/
INCLUDEFLAGS = $(patsubst %,-I% ,$(INCLUDEPATH))
# if you created a new subfolder in the source dir, you gotta list it here as well, so c-files are found
SUBFOLDERSRC = . /error /parse_map
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
		parse_util_2.c

#parser_main.c
	

		
OBJFNAME = $(SRC:.c=.o)
OBJ = $(patsubst %,$(PATHOBJ)%,$(OBJFNAME))

.PHONY: all clean fclean re fcleanall reall leaks

all: $(NAME)

$(NAME): $(PATHLIBFT) $(OBJ)
	$(LINK) $(CFLAGS) -o $(NAME) $(OBJ) $(PATHLIBFT)

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
	@echo -e "\n\n"
	@echo "Please copy/create supression file first: 'readline.supp' "
	@echo -e "\n\n"
	@make
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

reall: fcleanall all

re: fclean all

.PRECIOUS: $(PATHOBJ)%.o
