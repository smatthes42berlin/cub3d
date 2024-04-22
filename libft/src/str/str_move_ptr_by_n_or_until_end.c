#include "lib_main.h"

char	*str_move_ptr_by_n_or_until_end(const char *str, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		i++;
	}
	return ((char *)str + i);
}
