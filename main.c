#include "cub3d.h"

// int	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		// 1,
// 		1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 		0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 		1}, {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1}, {1, 0,
// 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0,
// 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0,
// 		0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 		0, 0, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 		1, 1, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 		0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 1,
// 		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}};

int	main(int argc, char *argv[])
{
	t_main_data		main_data;
	t_parse_state	parse_state;

	main_data.parse_state = &parse_state;
	init_main_data(&main_data, argc, argv);
	parse_main(&main_data);
	print_parse_res(&parse_state);
	free_parse_state(&parse_state);
	exit(1);
	// init(&main_data);
	// check correct number of args
	//
	// (void)argc;
	// (void)argv;
	return (0);
}

int	init_main_data(t_main_data *main_data, int argc, char *argv[])
{
	main_data->argc = argc;
	main_data->argv = argv;
	main_data->map.texture_east = NULL;
	main_data->map.texture_north = NULL;
	main_data->map.texture_south = NULL;
	main_data->map.color_ceiling[0] = 0;
	main_data->map.color_ceiling[1] = 0;
	main_data->map.color_ceiling[2] = 0;
	main_data->map.color_floor[0] = 0;
	main_data->map.color_floor[1] = 0;
	main_data->map.color_floor[2] = 0;
	main_data->map.texture_west = NULL;
	// main_data->map.map = NULL;
	return (0);
}
