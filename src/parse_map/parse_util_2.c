#include "cub3d.h"

bool	compare_line(t_parse_state *parse_state, const char *str)
{
	int	org;
	int	trimmed;

	org = (ft_strncmp(str, (char *)parse_state->cur_line->content,
				ft_strlen(str)) == 0);
	if (parse_state->cur_line_trimmed)
		trimmed = (ft_strncmp(str, parse_state->cur_line_trimmed,
					ft_strlen(str)) == 0);
	else
		trimmed = 0;
	return (org || trimmed);
}

bool	is_newline(t_parse_state *parse_state)
{
	return (compare_line(parse_state, "\n"));
}

t_optn_parse	*is_optn(t_parse_state *parse_state)
{
	if (compare_line(parse_state, parse_state->texture_east.identifier))
		return (&(parse_state->texture_east));
	if (compare_line(parse_state, parse_state->texture_north.identifier))
		return (&(parse_state->texture_north));
	if (compare_line(parse_state, parse_state->texture_south.identifier))
		return (&(parse_state->texture_south));
	if (compare_line(parse_state, parse_state->texture_west.identifier))
		return (&(parse_state->texture_west));
	if (compare_line(parse_state, parse_state->color_ceiling.identifier))
		return (&(parse_state->color_ceiling));
	if (compare_line(parse_state, parse_state->color_floor.identifier))
		return (&(parse_state->color_floor));
	return (NULL);
}

bool	is_map_start(t_parse_state *parse_state)
{
	char	*content;
	int		i;

	printf("is map start!\n");
	i = 0;
	content = parse_state->cur_line->content;
	while (ft_isspace(content[i]))
		i++;
	if (ft_str_chr_index("10WESN", content[i]) >= 0)
		return (true);
	return (false);
}

// any number of ws
// encounter either a 1, 0, W,E,S,N,
