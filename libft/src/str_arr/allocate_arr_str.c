#include "lib_main.h"

int	allocate_arr_str(char ***res, char prefill, int num_elem, int str_len)
{
	int	i;

	*res = NULL;
	i = 0;
	if (num_elem <= 0 || str_len < 0)
		return (0);
	*res = malloc(sizeof(**res) * (num_elem + 1));
	if (!*res)
		return (1);
	while (i < num_elem)
	{
		(*res)[i] = malloc(sizeof(***res) * (str_len + 1));
		if (!(*res)[i])
		{
			free_str_arr_null(*res);
			return (1);
		}
		if (prefill >= 0)
			str_fill((*res)[i], str_len, prefill);
		(*res)[i][str_len] = '\0';
		i++;
	}
	(*res)[i] = NULL;
	return (0);
}
