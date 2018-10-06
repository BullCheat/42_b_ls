/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

#define PERM(flag, c) printf("%c", mode & flag ? c : '-')

void	print_permissions(mode_t mode)
{
	printf(RESET "%c", get_file_type(mode));
	PERM(S_IRUSR, 'r');
	PERM(S_IWUSR, 'w');
	printf("%c", get_oth_type(mode, 0));
	PERM(S_IRGRP, 'r');
	PERM(S_IWGRP, 'w');
	printf("%c", get_oth_type(mode, 1));
	PERM(S_IROTH, 'r');
	PERM(S_IWOTH, 'w');
	printf("%c", get_oth_type(mode, 2));
	printf(" "); // TODO EAX
}

char	*human_time(struct stat *st)
{
	char *s;

#ifdef __APPLE__
	s = ctime(&st->st_mtimespec.tv_sec);
#else
	s = ctime(&st->st_mtim.tv_sec);
#endif
	s += 4;
	s[12] = 0;
	return (s);
}

t_list **split_list(t_list *files, int width, int *biggest, int *cols) {
	t_list **ret;
	int	lsize;
	int rows;
	t_list *tmp;

	*biggest = get_biggest_filename(files, &lsize) + 1;
	*cols = width / *biggest;
	if (*cols < 1)
		*cols = 1;
	rows = lsize / *cols + (lsize % *cols != 0);
	ret = malloc(*cols * sizeof(t_list*));
	for (int i = 0; i < *cols; i++) {
		ret[i] = files;
		if (i != *cols - 1)
			for (int j = 0; j < rows && files; j++)
			{
				tmp = files;
				files = files->next;
				if (j == rows - 1)
					tmp->next = 0;
			}
	}
	return (ret);
}

char *get_file_color(t_file *file)
{
	char type;

	type = get_file_type(file->stat->st_mode);
	if (type == '-' && file->stat->st_mode & 0111)
		return (RED);
	if (type == 'd')
		return (CYN);
	if (type == 'l')
		return (MAG);
	if (type == 'c')
		return (BYEL);
	if (type == 'b')
		return (BCYN);
	return (RESET);
}

void free_list(t_list *list, char elements) {
	t_list *tmp;

	while ((tmp = list))
	{
		list = tmp->next;
		if (elements && tmp->data)
		{
			free(tmp->data->name);
			if (tmp->data->cache)
			{
				free(tmp->data->cache->gname);
				free(tmp->data->cache->uname);
				free(tmp->data->cache);
			}
			if (tmp->data->stat)
				free(tmp->data->stat);
			free(tmp->data);
		}
		free(tmp);
	}
}

void free_lists(t_list **lists, size_t n, char elements)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		free_list(lists[i], elements);
		i++;
	}
	free(lists);
}

void	display_columns(t_list *files, int width)
{
	int	biggest;
	int cols;
	t_list **lists;
	int printed;

	lists = split_list(files, width, &biggest, &cols);
	while (*lists != NULL) {
		for (int i = 0; i < cols && lists[i]; i++) {
			printf("%s", get_file_color(lists[i]->data));
			printed = printf("%s", lists[i]->data->name);
			printf(RESET);
			if (i != cols - 1)
				printf("%*s", biggest - printed, "");
			lists[i] = lists[i]->next;
		}
		printf("\n");
	}
	free_lists(lists, (size_t) cols, 1);
}
#ifdef __APPLE__
void display_file_detailed(t_file *file, const t_file_lengths *lens)
{
	struct stat	*st;
	char 		link_buf[1024];

	st = file->stat;
	print_permissions(st->st_mode);
	printf(" %*u ", lens->links, st->st_nlink);
	printf("%-*s  ", lens->uname, file->cache->uname);
	printf("%-*s  ", lens->gname, file->cache->gname);
	if (!S_ISBLK(st->st_mode) && !S_ISCHR(st->st_mode))
		printf("%*llu ", lens->size, st->st_size);
	else
		printf(" %*u, %*u ", lens->major, major(st->st_rdev),
			   lens->minor, minor(st->st_rdev));
	printf("%s %s%s" RESET, human_time(st), get_file_color(file), file->name);
	if (S_ISLNK(st->st_mode))
		printf(" -> %s", read_link(file, link_buf, 1024));
	printf("\n");
}
#else
void display_file_detailed(t_file *file, const t_file_lengths *lens)
{
	struct stat	*st;
	char 		link_buf[1024];

	st = file->stat;
	print_permissions(st->st_mode);
	printf(" %*lu ", lens->links, st->st_nlink);
	printf("%-*s  ", lens->uname, file->cache->uname);
	printf("%-*s  ", lens->gname, file->cache->gname);
	if (!S_ISBLK(st->st_mode) && !S_ISCHR(st->st_mode))
		printf("%*lu ", lens->size, st->st_size);
	else
		printf(" %*lu, %*lu ", lens->major, MAJOR(st->st_rdev),
			lens->minor, MINOR(st->st_rdev));
	printf("%s %s%s" RESET, human_time(st), get_file_color(file), file->name);
	if (S_ISLNK(st->st_mode))
		printf(" -> %s", read_link(file, link_buf, 1024));
	printf("\n");
}
#endif

void	display_list(t_list *files)
{
	t_file_lengths lens;

	fill_cache(files);
	compute_lengths(files, &lens);
	if (!files->data->from_file_arg)
#ifdef __APPLE__
		printf("total %llu\n", count_blocks(files));
#else
		printf("total %lu\n", count_blocks(files));
#endif
	while (files && files->data)
	{
		display_file_detailed(files->data, &lens);
		files = files->next;
	}
	free_list(files, 1);
}
