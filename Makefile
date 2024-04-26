SHELL:=/bin/bash
CFLAGS = -g -O3 -Wall -Wextra -Werror $(INCLUDEFLAGS)
LDFLAGS = -lmlx -Lmlx -lXext -lX11 -lm
# LDFLAGS = -lmlx -Lmlx -lXext -lX11 -lm

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
SUBFOLDERSRC = . /error /parse_map /raycast /free /print /check_extracted_details/ /parse_util /check_pars_res
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
		parse_map_file.c \
		parse_main.c \
		parse_whole_file.c \
		init_parse_state.c \
		parse_util_1.c \
		parse_util_2.c \
		parse_util_3.c \
		parse_util_4.c \
		handle_map_start.c \
		handle_newline.c \
		handle_unknown.c \
		handle_optn.c \
		free_everything.c \
		print_map.c \
		print_parse_res.c \
		print_parse_util.c \
		check_extracted_details.c \
		check_map_main.c \
		check_map_start_pos.c \
		check_map_unknown_chars.c \
		check_option_col.c \
		check_option_tex.c \
		check_option_tex_2.c \
		check_map_flood_fill_util.c \
		check_map_flood_fill_util_2.c \
		check_map_flood_fill_rec_lim.c \
		check_map_undo_flood_fill.c \
		check_map_create_reachable_map.c \
		raycast.c \
		ray_horizontal.c \
		ray_vertical.c \
		clean.c \
		init.c \
		keys.c \
		draw_minimap.c \
		draw_line.c \
		draw_render.c \
		draw_player.c \
		wall_collision.c \
		math_utils.c \
		wall_ceiling_floor.c \
		color_buffer.c \
		check_parse_res_main.c \
		print_debug_parse.c

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
