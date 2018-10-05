/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_utils.h"

char		is_hidden(const char *f)
{
	return (f[0] == '.');
}

t_file		*get_data(char *dir, char *file, char is_file)
{
	t_file	*f;
	int		res;

	f = malloc(sizeof(t_file));
	f->name = file;
	f->dir = dir;
	f->from_file_arg = is_file;
	f->stat = malloc(sizeof(struct stat));
	res = lstat(ft_concat(dir, file), f->stat);
	if (res)
		printf("%s = %d -> %s\n", file, res, strerror(errno));
	return (f);
}

t_list		*fetch_files(char *file, char all)
{
	struct stat		data;
	t_list			*files;
	DIR				*dir;
	struct dirent	*content;

	if (stat(file, &data))
	{
		printf("ls: %s: %s\n", file, strerror(errno));
		return (NULL);
	}
	files = create_list();
	if (S_ISDIR(data.st_mode))
	{
		dir = opendir(file);
		while ((content = readdir(dir)))
			if (all || !is_hidden(content->d_name))
				list_push(files, get_data(file, ft_strdup(content->d_name), 0));
		closedir(dir);
	}
	else
		list_push(files, get_data("./", file, 1));
	return (files);
}

blkcnt_t	count_blocks(t_list *files)
{
	blkcnt_t i;

	i = 0;
	while (files && files->data)
	{
		i += files->data->stat->st_blocks;
		files = files->next;
	}
	return (i);
}
