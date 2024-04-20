#include "cub3d.h"

int	handle_quoted_path(t_optn_parse *col)
{
	char	**splitted;

	if (!closing_quote_found(col->line_in_map_file + 1,
			(col->line_in_map_file)[0]))
		return (wrong_format_ret_code(col, 0));
	if (closing_quote_not_last_char(col))
		return (wrong_format_ret_code(col, 0));
	splitted = ft_split(col->line_in_map_file + 1,
			(col->line_in_map_file)[0]);
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

int	wrong_format_ret_code(t_optn_parse *col, int code)
{
	col->wrong_format = true;
	return (code);
}
