#include "cub3d.h"

int	check_option_col(t_optn_parse *col)
{
	char	**splitted;

	remove_spaces_inplace(&(col->line_in_map_file));
	if (!col->line_in_map_file)
		return (0);
	if (ft_strlen(col->line_in_map_file) < 5)
	{
		col->wrong_format = true;
		return (0);
	}
	if (check_comma_error(col))
		return (0);
	splitted = ft_split_str(col->line_in_map_file, ",");
	if (!splitted)
		throw_error_sys_call((t_error_ms){errno, ERROR_MALLOC,
				"Cannot split col def line!"}, true);
	if (ft_arr_len_char(splitted) != 3)
	{
		free_str_arr_null(splitted);
		col->wrong_format = true;
		return (0);
	}
	get_val_rgb(col, splitted, 0);
	get_val_rgb(col, splitted, 1);
	get_val_rgb(col, splitted, 2);
	free_str_arr_null(splitted);
	return (0);
}

int	get_val_rgb(t_optn_parse *col, char **splitted, int index)
{
	int	res;

	if (!str_only_digits(splitted[index]))
	{
		col->wrong_format = true;
		return (0);
	}
	res = ft_atoi_secure(splitted[index]);
	if (res < 0 || res > 255)
	{
		col->rgb_out_of_range = true;
		return (0);
	}
	(col->color)[index] = res;
	return (0);
}

bool	check_comma_error(t_optn_parse *col)
{
	int		i;
	bool	one_comma;

	i = 0;
	i = 0;
	one_comma = false;
	if ((col->line_in_map_file)[0] == ',')
	{
		col->wrong_format = true;
		return (true);
	}
	while ((col->line_in_map_file)[i])
	{
		if ((col->line_in_map_file)[i] == ',')
		{
			if (one_comma)
			{
				col->wrong_format = true;
				return (true);
			}
			one_comma = true;
		}
		else
			one_comma = false;
		i++;
	}
	if ((col->line_in_map_file)[i - 1] == ',')
	{
		col->wrong_format = true;
		return (true);
	}
	return (false);
}
