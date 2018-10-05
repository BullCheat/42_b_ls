/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sort.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_SORT_H
# define FILE_SORT_H

# include "llist.h"
# include <sys/stat.h>

typedef struct		s_file_lengths
{
	int 			links;
	int 			uname;
	int 			gname;
	int 			size;
	int 			major;
	int 			minor;
}					t_file_lengths;

typedef struct		s_file_cache
{
	char 			*uname;
	char			*gname;
}					t_file_cache;

typedef struct		s_file
{
	char			*name;
	char			*dir;
	struct stat		*stat;
	char			from_file_arg;
	t_file_cache	*cache;
}					t_file;

char				compare_time(t_file *better, t_file *other);
char				compare_alpha(t_file *better, t_file *other);
char				compare(t_file *better, t_file *other, char reverse, char time);
t_file				*get_best_file(t_list *list, char reverse, char time);
void				sort_files(t_list **list, char reverse, char time);

#endif
