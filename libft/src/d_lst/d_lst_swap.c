#include "lib_main.h"

static void	swap_2(t_list_dc *head);
static void	swap_3(t_list_dc *head);

t_list_dc	*d_lst_swap(t_list_dc **lst)
{
	t_list_dc	*head;

	head = *lst;
	*lst = head->next;
	if (!lst || !head)
		return (NULL);
	if (dc_lst_exactly_one(head))
		return (head);
	if (dc_lst_exactly_two(head))
		swap_2(head);
	else
		swap_3(head);
	return (*lst);
}

static void	swap_2(t_list_dc *head)
{
	t_list_dc	*second;

	second = head->next;
	head->next = NULL;
	head->prev = second;
	second->next = head;
	second->prev = NULL;
}

static void	swap_3(t_list_dc *head)
{
	t_list_dc	*second;

	second = head->next;
	head->next = second->next;
	second->prev = NULL;
	second->next->prev = head;
	head->prev = second;
	second->next = head;
}
