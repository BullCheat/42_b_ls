/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_UTILS_H
# define FILE_UTILS_H

# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include "file_sort.h"

char		is_hidden(const char *f);
t_file		*get_data(char *dir, char *file, char is_file);
t_list		*fetch_files(char *file, char all);
blkcnt_t	count_blocks(t_list *files);

#endif
