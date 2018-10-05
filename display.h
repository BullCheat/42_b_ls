/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <ntsid.h>
# include <stdio.h>
# include <time.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include "llist.h"
# include "sort_utils.h"
# include "file_utils.h"
# include "file_sort.h"
# include "display_utils.h"

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36;1m"
# define WHT   "\x1B[37m"
# define BRED   "\x1B[41m"
# define BGRN   "\x1B[42m"
# define BYEL   "\x1B[34;43m"
# define BBLU   "\x1B[44m"
# define BMAG   "\x1B[45m"
# define BCYN   "\x1B[44;46m"
# define BWHT   "\x1B[47m"
# define RESET "\x1B[0m"

void	print_permissions(mode_t mode);
char	*human_time(struct stat *st);
void	display_columns(t_list *files, int width);
void	display_list(t_list *files);

#endif
