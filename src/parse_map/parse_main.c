#include "cub3d.h"

int	parse_main(t_main_data *main_data)
{
	int			fd;
	t_list_d	*file_lbl;

	if (main_data->argc != 2)
		throw_error_gen(1, "Wrong number of args!", true);
	if (!str_ends_on(main_data->argv[1], ".cub"))
		throw_error_gen(1, "Wrong extension input file!", true);
	fd = open(main_data->argv[1], O_RDONLY);
	if (fd == -1)
		throw_error_sys_call((t_error_ms){errno, ERROR_OPEN,
				"Cannot open Map file!"}, true);
	if (read_file_lines_to_list(fd, &file_lbl, true))
		throw_error_sys_call((t_error_ms){errno, ERROR_MALLOC,
				"Cannot read Map file!"}, true);
	if (REM_EMPTY_LINES_MAP_FILE)
		read_file_list_rem_empty_lines(file_lbl);
	if (close(fd))
		throw_error_sys_call((t_error_ms){errno, ERROR_CLOSE,
				"Cannot close Map file!"}, true);
	parse_map_file(main_data, file_lbl);
	d_lst_clear(&file_lbl, free);
	return (0);
}
