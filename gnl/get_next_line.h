/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjohnnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:09:30 by tjohnnie          #+#    #+#             */
/*   Updated: 2021/01/15 20:09:32 by tjohnnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "stdlib.h"
# include "unistd.h"
# define BUFFER_SIZE 1024

int					get_next_line(int fd, char **line);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char *s1, char *s2);

#endif
