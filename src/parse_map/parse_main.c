#include "cub3d.h"

int	parse_main(t_main_data *main_data)
{
	int			fd;
	t_list_d	*file_lbl;

	if (main_data->argc != 2)
		throw_error_map_file(1, "Wrong number of args!", true);
	fd = open(main_data->argv[1], O_RDONLY);
	if (fd == -1)
		throw_error_sys_call((t_error_ms){errno, ERROR_OPEN,
				"Cannot open Map file!"}, true);
	if (read_file_lines_to_list(fd, &file_lbl))
		throw_error_sys_call((t_error_ms){errno, ERROR_MALLOC,
				"Cannot read Map file!"}, true);
	// read_file_list_rem_newlines(file_lbl);
	if (close(fd))
		throw_error_sys_call((t_error_ms){errno, ERROR_CLOSE,
				"Cannot close Map file!"}, true);
	parse_map(main_data, file_lbl);
	d_lst_clear(&file_lbl, free);
	return (0);
}

// check if all necessary lines exists exactly one time before reaching map

int	parse_map(t_main_data *main_data, t_list_d *file_lbl)
{
	t_list_d	*cur_line;

	cur_line = file_lbl;
	while (cur_line)
	{
		printf("line: %s", (char *)cur_line->content);
		cur_line = cur_line->next;
	}
	main_data->argc++;
	return (0);
}

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

// ways to break map
// https://gist.github.com/maxdesalle/5e9d1dec0799e6f57f66ee4e35243b74
// Resolution
// putting a negative resolution
// adding a third resolution number
// leaving only one resolution number
// replacing the space between the two resolution numbers with a tab
// adding a random letter in the resolution
// placing a resolution greater than the actual screen size
// remove the resolution (the whole line)
// enter at two different places the resolution
// change a resolution number to a number above the size of an integer (a value above 2147483647)
// Textures
// add a false texture (like Z ./texturepath)
// try a texture path without the starting '.'
// remove the 'm' in .xpm at the end of a texture path
// put all directions in the same textures
// add two times the same texture direction
// remove a texture direction
// add a random letter before or after the texture path
// add a random number before or after the texture path
// Colors
// put a number in RGB great than the 255,255,255 limit
// remove one number to only have 2 numbers (255,255 for example)
// add a fourth number
// try with 3 numbers, but with 3 commas
// add a random letter before or after
// add a random number before or after
// add a random letter in-between
// remove one of the color lines
// enter a color line two times
// Map
// Add an empty line in the map itself
// Enter two player positions
// Remove the player position
// Add a random letter in the map
// Add a random number in the map
// Remove a wall at the outside of the map, and replace it with a space (0)
// Remove a wall at the outside of the map, and replace it with a sprite (2)
// Place the map above the other elements in the file