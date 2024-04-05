#include "cub3d.h"

int	parse_main(t_main_data *main_data)
{
	int			fd;
	t_list_d	*file_lbl;

	if (main_data->argc != 2)
		throw_error_gen(1, "Wrong number of args!", true);
	fd = open(main_data->argv[1], O_RDONLY);
	if (fd == -1)
		throw_error_sys_call((t_error_ms){errno, ERROR_OPEN,
			"Cannot open Map file!"}, true);
	if (read_file_lines_to_list(fd, &file_lbl))
		throw_error_sys_call((t_error_ms){errno, ERROR_MALLOC,
			"Cannot read Map file!"}, true);
	if (REM_EMPTY_LINES_MAP_FILE)
		read_file_list_rem_newlines(file_lbl);
	if (close(fd))
		throw_error_sys_call((t_error_ms){errno, ERROR_CLOSE,
			"Cannot close Map file!"}, true);
	parse_map(main_data, file_lbl);
	d_lst_clear(&file_lbl, free);
	return (0);
}

// check if all necessary lines exists exactly one time before reaching map
// vom groben ins feine

// parse whole file and keep track of things zou find

int	parse_map(t_main_data *main_data, t_list_d *file_lbl)
{
	t_parse_state	parse_state;

	init_parse_state(&parse_state, main_data, file_lbl);
	while (parse_state.cur_line)
	{
		identify_line(&parse_state);
	}
	return (0);
}

int	identify_line(t_parse_state *parse_state)
{
	printf("line: %s\n", (char *)parse_state->cur_line->content);
	if (is_newline(parse_state))
		printf("newline");
	go_to_next_line(parse_state);
	return (0);
}

// check nothing after map
// check all required fields before map only once
// check no unknown fields
// check only numbers and on letter in map
//

// try to open texture file, to see if it exists
// map muss zusammenhaengend sein, bzw. replace all spaces with 0 or 1

// only one of N,S,E,W in map
// map is closed
// spaces must be enclosed by walls
// only ensure, they player cant step on any spaces or off the map
// pathfinding

// map always last
// everything except for map can be separated by one or more empty lines
// except for map eny element can be set in any order
// each type of information from an element can be seperated by one or more spaces
