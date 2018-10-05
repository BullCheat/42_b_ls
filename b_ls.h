/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_LS_H
# define B_LS_H

# include <stdio.h>
# include <sys/ioctl.h>
# include "sort_utils.h"
# include "file_utils.h"
# include "file_sort.h"
# include "string_utils.h"
# include "llist.h"
# include "display.h"

typedef struct	s_flags
{
	char		a;
	char		l;
	char		r;
	char		t;
}				t_flags;

void			b_ls(char *folder, t_flags *flags, int width);

#endif
