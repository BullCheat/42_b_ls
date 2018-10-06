/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_UTILS_H
# define DISPLAY_UTILS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <stdio.h>
# include <unistd.h>
# include "file_sort.h"

char	get_file_type(mode_t mode);
char	get_oth_type(mode_t mode, char i);
char	*read_link(const t_file *file, char *buffer, size_t buf_size);
void 	compute_lengths(const t_list *files, t_file_lengths *lens);
void 	fill_cache(t_list *files);

#endif
