#include "lib_main.h"

t_list_dc	*d_lst_last(t_list_dc *lst)
{
	t_list_dc	*last;

	if (lst == NULL)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}
