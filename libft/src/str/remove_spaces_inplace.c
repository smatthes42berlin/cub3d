#include "lib_main.h"

int	remove_spaces_inplace(char **str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while ((*str)[i])
	{
		if (ft_isspace((*str)[i]))
			move_all_by_one(str, i);
		else
			i++;
	}
	return (0);
}
