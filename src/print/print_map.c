#include "cub3d.h"

int	print_map(char **map, int width, int height)
{
	int	i;
	int	j;

	j = 0;
	if (!map || !*map)
		return (0);
	printf("map start\n");
	printf("height: %d\n", width);
	printf("width: %d\n", height);
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
	printf("map end\n");
	return (0);
}
