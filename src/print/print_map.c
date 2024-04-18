#include "cub3d.h"

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
