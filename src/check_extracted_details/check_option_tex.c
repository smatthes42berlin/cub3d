#include "cub3d.h"

int	check_option_tex(t_optn_parse *col)
{
	if (!col->line_in_map_file || str_is_empty(col->line_in_map_file))
	{
		free(col->line_in_map_file);
		col->line_in_map_file = NULL;
		return (0);
	}
	check_path_format(col);
	check_path_extension(col);
	check_file_access(col);
	return (0);
}

int	check_file_access(t_optn_parse *col)
{
	int	fd;

	fd = open(col->line_in_map_file, O_RDONLY);
	if (fd < 0)
	{
		col->file_access = false;
		return (0);
	}
	if (close(fd) < 0)
		throw_error_sys_call_parse((t_error_ms){errno, ERROR_CLOSE,
				"Cannot close texture image file!"}, col->parse_state, true);
	return (0);
}

// if (str_ends_on(col->line_in_map_file, ".png"))
// 	col->wrong_format = false;

int	check_path_extension(t_optn_parse *col)
{
	col->wrong_format = true;
	if (str_ends_on(col->line_in_map_file, ".xpm"))
		col->wrong_format = false;
	return (0);
}

int	check_path_format(t_optn_parse *col)
{
	if (is_quote(col->line_in_map_file[0]))
		handle_quoted_path(col);
	else
		handle_unquoted_path(col);
	return (0);
}

int	handle_unquoted_path(t_optn_parse *col)
{
	char	**splitted;

	splitted = ft_split(col->line_in_map_file, ' ');
	if (!splitted)
		throw_error_sys_call_parse((t_error_ms){errno, ERROR_MALLOC,
				"Cannot split tex def line!"}, col->parse_state, true);
	if (ft_arr_len_char(splitted) != 1)
	{
		free_str_arr_null(splitted);
		col->wrong_format = true;
		return (0);
	}
	free(col->line_in_map_file);
	col->line_in_map_file = splitted[0];
	free(splitted);
	return (0);
}
