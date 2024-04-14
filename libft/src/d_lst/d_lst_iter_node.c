#include "lib_main.h"

void	d_lst_iter_node(t_list_dc *lst, void (*f)(void *))
{
	t_list_dc	*current;

	if (!lst)
		return ;
	f(lst);
	current = lst->next;
	while (current)
	{
		f(current);
		current = current->next;
	}
}
