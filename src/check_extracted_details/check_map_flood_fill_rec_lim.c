#include "cub3d.h"

int	flood_fill_rec_lim(t_parse_state *parse_state)
{
	int	start_width;
	int	start_height;
	int	cur_point[2];

	start_height = parse_state->map_parse.start_pos_o[0];
	start_width = parse_state->map_parse.start_pos_o[1];
	parse_state->map_parse.reachable_width_min = start_width;
	parse_state->map_parse.reachable_width_max = start_width;
	parse_state->map_parse.reachable_height_min = start_height;
	parse_state->map_parse.reachable_height_max = start_height;
	parse_state->map_parse.org_rect[start_height][start_width] = '0';
	add_point_to_queue(parse_state, start_height, start_width);
	while (parse_state->map_parse.queue)
	{
		get_cur_point_queue(parse_state, cur_point);
		flood_check_rec_lim(parse_state, cur_point[0], cur_point[1], 0);
		remove_point_from_queue(parse_state);
	}
	return (0);
}

int	flood_check_rec_lim(t_parse_state *parse_state, int height, int width,
		int rec_depth)
{
	int	cur_point[2];

	cur_point[0] = height;
	cur_point[1] = width;
	rec_depth++;
	if (check_end_point_reached(parse_state, cur_point))
		return (0);
	if (parse_state->map_parse.org_rect[height][width] == '0')
	{
		parse_state->map_parse.org_rect[height][width] = '_';
		if (rec_depth < MAX_REC_DEPTH)
			recursion_surrounding_points(parse_state, cur_point, rec_depth);
		else
		{
			add_surrounding_points_queue(parse_state, cur_point);
			return (1);
		}
	}
	check_map_not_closed(parse_state, height, width);
	adjust_reachable_map(parse_state, height, width);
	return (0);
}

bool	check_end_point_reached(t_parse_state *parse_state, int cur_point[2])
{
	int	height;
	int	width;

	height = cur_point[0];
	width = cur_point[1];
	if (cur_point[0] + 1 > parse_state->map_parse.max_height_org
		|| cur_point[0] < 0)
		return (true);
	if (cur_point[1] + 1 > parse_state->map_parse.max_width_org
		|| cur_point[1] < 0)
		return (true);
	if (parse_state->map_parse.org_rect[height][width] == '_'
		|| parse_state->map_parse.org_rect[height][width] == '1')
		return (true);
	return (false);
}

int	recursion_surrounding_points(t_parse_state *parse_state, int cur_point[2],
		int rec_depth)
{
	flood_check_rec_lim(parse_state, cur_point[0] + 1, cur_point[1], rec_depth);
	flood_check_rec_lim(parse_state, cur_point[0] - 1, cur_point[1], rec_depth);
	flood_check_rec_lim(parse_state, cur_point[0], cur_point[1] + 1, rec_depth);
	flood_check_rec_lim(parse_state, cur_point[0], cur_point[1] - 1, rec_depth);
	if (MAP_DIAG_CHECK)
	{
		flood_check_rec_lim(parse_state, cur_point[0] + 1, cur_point[1] + 1,
				rec_depth);
		flood_check_rec_lim(parse_state, cur_point[0] - 1, cur_point[1] - 1,
				rec_depth);
		flood_check_rec_lim(parse_state, cur_point[0] + 1, cur_point[1] - 1,
				rec_depth);
		flood_check_rec_lim(parse_state, cur_point[0] - 1, cur_point[1] + 1,
				rec_depth);
	}
	return (0);
}
