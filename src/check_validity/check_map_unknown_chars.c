#include "cub3d.h"

int	check_unknown_characters(t_parse_state *parse_state)
{
	int	height;
	int	width;

	height = 0;
	while (height < parse_state->map_parse.max_height_org)
	{
		width = 0;
		while (width < parse_state->map_parse.max_width_org)
		{
			if (ft_str_chr_index("NWSE 10-",
									parse_state->map_parse.org_rect[height][width]) < 0)
				return (set_bool_field(&(parse_state->map_parse.unknown_char),
						true, 0));
			width++;
		}
		height++;
	}
	return (0);
}
