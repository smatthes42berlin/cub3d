#include "cub3d.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	closing_quote_found(char *cli_input, char quote_type)
{
	return (ft_str_chr_index(cli_input, quote_type) >= 0);
}

bool	closing_quote_not_last_char(t_optn_parse *col)
{
	return (ft_str_chr_index(col->line_in_map_file + 1,
			(col->line_in_map_file)[0]) != 
			(ssize_t)ft_strlen(col->line_in_map_file + 1) - 1);
}
