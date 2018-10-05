/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_list	*create_list(void)
{
	return (ft_memalloc(sizeof(t_list)));
}

void	list_push(t_list *list, struct s_file *element)
{
	if (!list)
		return ;
	while (list->data && list->next)
		list = list->next;
	if (list->data)
	{
		list->next = create_list();
		list = list->next;
	}
	list->data = element;
}

void	list_remove(t_list **list, struct s_file *element)
{
	t_list *tmp;
	t_list *local;

	if (!*list)
		return ;
	if ((*list)->data == element)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		return ;
	}
	local = *list;
	while (local->next && local->next->data != element)
		local = local->next;
	if (local->next)
	{
		tmp = local->next;
		local->next = tmp->next;
		free(tmp);
	}
}
