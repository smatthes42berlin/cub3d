#include "lib_main.h"

t_list_dc	*d_lst_map(t_list_dc *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list_dc	*cur_old;
	t_list_dc	*new_head;
	t_list_dc	*new_node;

	new_head = NULL;
	if (lst == NULL)
		return (new_head);
	new_head = d_lst_new(f(lst->content));
	if (!new_head)
		return (NULL);
	cur_old = lst->next;
	while (cur_old)
	{
		new_node = d_lst_new(f(cur_old->content));
		if (!new_node)
		{
			d_lst_clear(&new_head, del);
			return (NULL);
		}
		d_lst_add_back(&new_head, new_node);
		cur_old = cur_old->next;
	}
	return (new_head);
}
