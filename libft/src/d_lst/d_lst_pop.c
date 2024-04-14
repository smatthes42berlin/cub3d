#include "lib_main.h"

t_list_dc	*d_lst_pop(t_list_dc **lst)
{
	t_list_dc	*old_head;

	if (!lst || !*lst)
		return (NULL);
	old_head = *lst;
	if (d_lst_exactly_one(*lst))
		*lst = NULL;
	else
	{
		*lst = old_head->next;
		old_head->next->prev = NULL;
	}
	old_head->next = NULL;
	old_head->prev = NULL;
	return (old_head);
}
