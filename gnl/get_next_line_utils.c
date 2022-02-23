/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjohnnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:10:18 by tjohnnie          #+#    #+#             */
/*   Updated: 2021/01/15 20:10:20 by tjohnnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	if (!s)
		return (0);
	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		n;
	size_t	size_copy;

	if (!(dst) || !(src))
		return (0);
	size_copy = size;
	n = 0;
	while (src[n] != '\0' && size-- > 1)
	{
		dst[n] = src[n];
		n++;
	}
	if (size_copy > 0)
		dst[n] = '\0';
	return ((size_t)ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	size;

	size = ft_strlen(s1) + 1;
	p = malloc(size);
	if (p == 0)
		return (0);
	ft_strlcpy(p, (char *)s1, size);
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	size;
	char	*copy;

	copy = s1;
	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(size + 1);
	if (str == 0)
		return (0);
	while (*s1 != '\0')
		*str++ = *s1++;
	while (*s2 != '\0')
		*str++ = *s2++;
	*str = '\0';
	free(copy);
	return (str - size);
}
