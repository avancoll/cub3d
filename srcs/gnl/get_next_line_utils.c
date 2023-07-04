/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:36:51 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/04 13:45:05 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
		if (*str++ == c)
			return (--str);
	return (NULL);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*str;
	int				i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	dest = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (dst < src)
		while (++i < (int)len)
			dest[i] = str[i];
	else if (src && dst > src)
		while (len-- > 0)
			dest[len] = str[len];
	return (dst);
}

char	*ft_strstock(char *s1, char *s2, int param)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	ptr = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		ptr[i++] = s1[j++];
	while (s2 && *s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	if (param)
		free(s1);
	return (ptr);
}

char	*ft_strndup(char *str, int n)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc(sizeof(char) * (n + 1));
	if (!newstr)
		return ((void *)0);
	i = -1;
	while (str && str[++i] && i < n)
		newstr[i] = str[i];
	newstr[i] = '\0';
	return (newstr);
}
