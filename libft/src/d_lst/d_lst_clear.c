#include "lib_main.h"

void	d_lst_clear(t_list_dc **lst, void (*del)(void *))
{
	t_list_dc	*temp;
	t_list_dc	*current;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current->next)
	{
		temp = current;
		current = current->next;
		d_lst_del_one(temp, del);
	}
	d_lst_del_one(current, del);
	*lst = NULL;
}
