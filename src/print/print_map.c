#include "cub3d.h"

int	print_map_parsing(t_parse_state *parse_state, const char which)
{
	if (which == 'o')
	{
		printf("original map\n");
		print_map(parse_state->map_parse.org_rect,
			parse_state->map_parse.max_width_org,
			parse_state->map_parse.max_height_org);
	}
	if (which == 'r')
	{
		printf("reachable map\n");
		if (!parse_state->map_parse.reachable_rect)
			printf("not defined\n");
		print_map(parse_state->map_parse.reachable_rect,
			parse_state->map_parse.reachable_width_max
			- parse_state->map_parse.reachable_width_min + 3,
			parse_state->map_parse.reachable_height_max
			- parse_state->map_parse.reachable_height_min + 3);
	}
	return (0);
}

int	print_map(char **map, int width, int height)
{
	int	i;
	int	j;

	j = 0;
	if (!map || !*map)
		return (0);
	printf("map start\n");
	printf("height: %d\n", height);
	printf("width: %d\n\n", width);
	while (j < height)
	{
		i = 0;
		printf("$");
		while (i < width)
		{
			printf("%c", map[j][i]);
			i++;
		}
		printf("$\n");
		j++;
	}
	printf("\nmap end\n");
	return (0);
}
