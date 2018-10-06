/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

char	parse_flag(char *s, t_flags *flags)
{
	if (*s == '-')
		return (1);
	while (*s)
	{
		if (*s == 'a')
			flags->a = 1;
		else if (*s == 'l')
			flags->l = 1;
		else if (*s == 'r')
			flags->r = 1;
		else if (*s == 't')
			flags->t = 1;
		else
		{
			printf("ls: illegal option -- %c\n", *s);
			printf("usage: ls [-alrt] [file ...]\n");
			exit(1);
		}
		s++;
	}
	return (0);
}

t_flags	*parse_flags(int argc, char **argv)
{
	t_flags	*flags;
	size_t	i;

	flags = ft_memalloc(sizeof(t_flags));
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			if (parse_flag(argv[i] + 1, flags))
				break ;
		i++;
	}
	return (flags);
}

int		main(int argc, char **argv)
{
	t_flags	*flags;
	size_t	i;
	char	called;
	char	ignore;
	struct winsize w;

	flags = parse_flags(argc, argv);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col < 80)
		w.ws_col = 80;
	i = 1;
	ignore = 0;
	called = 0;
	while (i < argc)
	{
		if (ignore || argv[i][0] != '-')
		{
			called = 1;
			b_ls(argv[i], flags, w.ws_col);
		}
		if ('-' == argv[i][0] && '-' == argv[i][1] && argv[i][2] == 0)
			ignore = 1;
		i++;
	}
	if (!called)
		b_ls(".", flags, w.ws_col);
	free(flags);
}
