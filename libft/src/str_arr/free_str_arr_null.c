#include "lib_main.h"

void	free_str_arr_null(char **str_arr)
{
	int	i;

	i = 0;
	if (!str_arr || !str_arr[0])
		return ;
	while (str_arr[i])
	{
		free(str_arr[i]);
		str_arr[i] = NULL;
		i++;
	}
	free(str_arr);
	str_arr = NULL;
}
