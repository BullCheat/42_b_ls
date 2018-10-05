/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrean <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 00:40:11 by adrean            #+#    #+#             */
/*   Updated: 2018/10/04 00:40:11 by adrean           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"

size_t	ft_strlen(const char *str)
{
	size_t s;

	s = 0;
	while (str[s])
		s++;
	return (s);
}

char	*ft_concat(char *dir, char *file)
{
	char	*ret;
	char	last;
	size_t	i;

	i = 0;
	ret = malloc(ft_strlen(dir) + ft_strlen(file) + 2);
	last = 0;
	while (*dir)
	{
		last = *dir;
		ret[i++] = *dir++;
	}
	if (last != '/')
		ret[i++] = '/';
	while (*file)
		ret[i++] = *file++;
	ret[i] = 0;
	return (ret);
}

void	*ft_memalloc(size_t s)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(s);
	i = 0;
	while (i < s)
		ptr[i++] = 0;
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;

	copy = malloc(ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

int		ft_numlen(off_t num)
{
	int i;

	if (!num)
		return (1);
	i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}
