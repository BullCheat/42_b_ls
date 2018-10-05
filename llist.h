/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLIST_H
# define LLIST_H

# include <string.h>
# include <stdlib.h>
# include "string_utils.h"

typedef struct		s_list
{
	struct s_file	*data;
	struct s_list	*next;
}					t_list;

void				list_push(t_list *list, struct s_file *element);
void				list_remove(t_list **list, struct s_file *element);
t_list				*create_list();

#endif
