#include "lib_main.h"

int	read_file_list_rem_empty_lines(t_list_d *list)
{
	t_list_d	*rem;

	while (list)
	{
		if (!ft_strcmp("\n", (char *)(list->content))
			|| str_is_empty((char *)(list->content)))
		{
			rem = d_lst_pop_current(&list);
			d_lst_del_one(rem, free);
		}
		else
			list = list->next;
	}
	return (0);
}
