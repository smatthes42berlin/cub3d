#include "lib_main.h"

static int	remove_spaces_back(char **str);
static int	remove_spaces_front(char **str);

int	str_trim_inplace(char **str)
{
	if (!str || !*str)
		return (0);
	remove_spaces_front(str);
	remove_spaces_back(str);
	return (0);
}

static int	remove_spaces_back(char **str)
{
	int	str_len;
	int	i;

	i = 0;
	str_len = ft_strlen(*str);
	while (i < str_len - 1)
	{
		if (!ft_isspace((*str)[str_len - 1 - i]))
			break ;
		(*str)[str_len - 1 - i] = '\0';
		i++;
	}
	return (0);
}

static int	remove_spaces_front(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if (!ft_isspace((*str)[i]))
			break ;
		move_all_by_one(str, i);
	}
	return (0);
}
