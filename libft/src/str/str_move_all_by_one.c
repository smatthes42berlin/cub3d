#include "lib_main.h"


int	move_all_by_one(char **str, int i)
{
	int	j;

	j = 0;
	while ((*str)[i + j + 1])
	{
		(*str)[i + j] = (*str)[i + j + 1];
		j++;
	}
	return (0);
}
