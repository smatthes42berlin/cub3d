#include "lib_main.h"

void	d_lst_iter_content(t_list_dc *lst, void (*f)(void *))
{
	t_list_dc	*current;

	if (!lst)
		return ;
	f(lst->content);
	current = lst->next;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}
