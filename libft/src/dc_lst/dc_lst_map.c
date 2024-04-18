#include "lib_main.h"

static t_list_dc	*clear_ret_null(t_list_dc **new_head, void (*del)(void *));

t_list_dc	*dc_lst_map(t_list_dc *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list_dc	*old_head;
	t_list_dc	*cur_old;
	t_list_dc	*new_head;
	t_list_dc	*new_node;

	new_head = NULL;
	old_head = lst;
	if (lst == NULL)
		return (new_head);
	new_head = dc_lst_new(f(lst->content));
	if (!new_head)
		return (NULL);
	cur_old = lst->next;
	while (old_head != cur_old)
	{
		new_node = dc_lst_new(f(cur_old->content));
		if (!new_node)
			return (clear_ret_null(&new_head, del));
		dc_lst_add_back(&new_head, new_node);
		cur_old = cur_old->next;
	}
	return (new_head);
}

static t_list_dc	*clear_ret_null(t_list_dc **new_head, void (*del)(void *))
{
	dc_lst_clear(new_head, del);
	return (NULL);
}
