#include "cub3d.h"

// start at start
// push the 4 reachable positions to queue, if they are zeros
// not o

int	flood_fill_it(t_parse_state *parse_state)
{
	int	start_width;
	int	start_height;

	print_map(parse_state->map_parse.org_rect,
				parse_state->map_parse.max_width_org,
				parse_state->map_parse.max_height_org);
	start_height = parse_state->map_parse.start_pos[0];
	start_width = parse_state->map_parse.start_pos[1];
	parse_state->map_parse.reachable_width_min = start_width;
	parse_state->map_parse.reachable_width_max = start_width;
	parse_state->map_parse.reachable_height_min = start_height;
	parse_state->map_parse.reachable_height_max = start_height;
	parse_state->map_parse.org_rect[start_height][start_width] = '0';
	add_point_to_queue(parse_state, start_height, start_width);
	flood_check_it(parse_state);
	return (0);
}

int	flood_check_it(t_parse_state *parse_state)
{
	int	cur_point[2];

	while (parse_state->map_parse.queue)
	{
		get_cur_point_queue(parse_state, cur_point);
		if (check_point_needs_test(parse_state, cur_point))
		{
			if (parse_state->map_parse.org_rect[cur_point[0]][cur_point[1]] == '0')
			{
				parse_state->map_parse.org_rect[cur_point[0]][cur_point[1]] = 'X';
				add_surrounding_points_queue(parse_state, cur_point);
			}
			check_map_not_closed(parse_state, cur_point[0], cur_point[1]);
			adjust_reachable_map(parse_state, cur_point[0], cur_point[1]);
		}
		remove_point_from_queue(parse_state);
	}
	return (0);
}

bool	check_point_needs_test(t_parse_state *parse_state,
							int *cur_point)
{
	int	h;
	int	w;

	h = cur_point[0];
	w = cur_point[1];
	if ((h + 1 > parse_state->map_parse.max_height_org || h < 0))
		return (false);
	if (w + 1 > parse_state->map_parse.max_width_org || w < 0)
		return (false);
	if (
		parse_state->map_parse.org_rect[h][w] == 'X'
			|| parse_state->map_parse.org_rect[h][w] == '1')
		return (false);
	return (true);
}
