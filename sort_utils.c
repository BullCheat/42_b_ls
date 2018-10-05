/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_utils.h"

int	get_biggest_filename(t_list *list, int *counter)
{
	size_t max;
	size_t temp;

	max = 0;
	if (counter != NULL)
		*counter = 0;
	while (list && list->data)
	{
		if (counter != NULL)
			*counter += 1;
		temp = ft_strlen(list->data->name);
		if (temp > max)
			max = temp;
		list = list->next;
	}
	return (int)(max);
}
