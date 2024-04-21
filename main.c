#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_main_data		main_data;
	t_parse_state	parse_state;

	main_data.parse_state = &parse_state;
	init_main_data(&main_data, argc, argv);
	parse_main(&main_data);
	free_parse_state(&parse_state);
	printf("Success\n");
	exit(1);
	// init(&main_data);
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
