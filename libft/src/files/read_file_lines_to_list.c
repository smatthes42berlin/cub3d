#include "lib_main.h"

int	read_file_lines_to_list(int fd, t_list_d **res)
{
	char	*next_line;
	t_list_d	*new;

	*res = NULL;
	next_line = get_next_line(fd);
	while (next_line)
	{
		new = d_lst_new(next_line);
		if (!new)
		{
			d_lst_clear(res, free);
			return (1);
		}
		d_lst_add_back(res, new);
		next_line = get_next_line(fd);
	}
	return (0);
}
