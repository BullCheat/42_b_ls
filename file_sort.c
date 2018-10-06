/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_sort.h"

char	compare_time(t_file *better, t_file *other)
{
	time_t a;
	time_t b;
#ifdef __APPLE__
	a = better->stat->st_mtimespec.tv_sec;
	b = other->stat->st_mtimespec.tv_sec;
#else
	a = better->stat->st_mtim.tv_sec;
	b = other->stat->st_mtim.tv_sec;
#endif
	if (a > b)
		return (1);
	else if (a == b)
		return (0);
	else
		return (-1);
}

char	compare_alpha(t_file *better, t_file *other)
{
	size_t i;

	i = 0;
	while (better->name[i] && better->name[i] == other->name[i])
		i++;
	if (better->name[i] < other->name[i])
		return (1);
	else
		return (-1);
}

char	compare(t_file *better, t_file *other, char reverse, char time)
{
	char res;

	if (time)
		res = compare_time(better, other);
	else
		res = 0;
	if (!res)
		res = compare_alpha(better, other);
	if (reverse)
		res *= -1;
	return (res);
}

t_file	*get_best_file(t_list *list, char reverse, char time)
{
	t_file *best;

	best = list->data;
	list = list->next;
	while (list && list->data)
	{
		if (compare(list->data, best, reverse, time) > 0)
			best = list->data;
		list = list->next;
	}
	return (best);
}

void	sort_files(t_list **list, char reverse, char time)
{
	t_list *sorted;
	t_file *best;

	sorted = create_list();
	while (*list && (*list)->data)
	{
		best = get_best_file(*list, reverse, time);
		list_remove(list, best);
		list_push(sorted, best);
	}
	free(*list);
	*list = sorted;
}
