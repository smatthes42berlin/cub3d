#include "lib_main.h"

int	read_file_lines_to_list(int fd, t_list_d **res,
		bool remove_newline_end_of_line)
{
	char		*next_line;
	int			line_length;
	t_list_d	*new;

	*res = NULL;
	next_line = get_next_line(fd);
	while (next_line)
	{
		if (remove_newline_end_of_line)
		{
			line_length = ft_strlen(next_line);
			if (next_line[line_length - 1] == '\n')
				next_line[line_length - 1] = '\0';
		}
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
