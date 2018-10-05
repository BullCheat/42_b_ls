/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display_utils.h"
#include "ft_itoa.h"

char	get_oth_type(mode_t mode, char i)
{
	char x;

	if (i == 0)
		x = S_IXUSR;
	else if (i == 1)
		x = S_IXGRP;
	else
		x = S_IXOTH;
	x = (char)('X' + (((x & mode) != 0) << 5));
	if (i == 0 && mode & S_ISUID)
		x += 'S' - 'X';
	if (i == 1 && mode & S_ISGID)
		x += 'S' - 'X';
	if (i == 2 && mode & S_ISVTX)
		x += 'T' - 'X';
	if (x == 'X')
		x = '-';
	return (x);
}

char	get_file_type(mode_t mode)
{
	mode &= S_IFMT;
	if (mode == S_IFREG)
		return ('-');
	if (mode == S_IFDIR)
		return ('d');
	if (mode == S_IFBLK)
		return ('b');
	if (mode == S_IFLNK)
		return ('l');
	if (mode == S_IFSOCK)
		return ('s');
	if (mode == S_IFCHR)
		return ('c');
	if (mode == S_IFIFO)
		return ('p');
	printf("MODE ERROR\n");
	return ('-');
}

char	*read_link(const t_file *file, char *buffer, size_t buf_size)
{
	ssize_t len;

	len = readlink(ft_concat(file->dir, file->name), buffer, buf_size - 1);
	if (len == -1)
		return ("<ERROR>");
	buffer[len] = 0;
	return (buffer);
}

void 	fill_cache(t_list *files)
{
	struct passwd	*udata;
	struct group	*gdata;

	while (files && files->data)
	{
		udata = getpwuid(files->data->stat->st_uid);
		gdata = getgrgid(files->data->stat->st_gid);
		files->data->cache = malloc(sizeof(t_file_cache));
		if (udata->pw_name != NULL && udata->pw_name[0] != 0)
			files->data->cache->uname = ft_strdup(udata->pw_name);
		else
			files->data->cache->uname = ft_itoa(udata->pw_uid);
		if (gdata->gr_name != NULL && gdata->gr_name[0] != 0)
			files->data->cache->gname = ft_strdup(gdata->gr_name);
		else
			files->data->cache->gname = ft_itoa(gdata->gr_gid);
		files = files->next;
	}
}

#define U(prop, val) lens->prop = lens->prop > val ? lens->prop : val

void 	compute_lengths(const t_list *files, t_file_lengths *lens)
{
	t_file	*f;
	int tmp;

	lens->links = 0;
	lens->uname = 0;
	lens->gname = 0;
	lens->size = 0;
	lens->major = 0;
	lens->minor = 0;
	while (files && files->data)
	{
		f = files->data;
		U(links, ft_numlen(f->stat->st_nlink));
		U(uname, (int)ft_strlen(f->cache->uname));
		U(gname, (int)ft_strlen(f->cache->gname));
		if (!S_ISBLK(f->stat->st_mode) && !S_ISCHR(f->stat->st_mode))
		{
			U(size, ft_numlen(f->stat->st_size));
		}
		else
		{
			U(major, ft_numlen(major(f->stat->st_rdev)));
			tmp = minor(f->stat->st_rdev);
			if (tmp < 256)
				U(minor, ft_numlen(tmp));
		}
		files = files->next;
	}
}
