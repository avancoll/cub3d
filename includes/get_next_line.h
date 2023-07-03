/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:05:54 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/03 21:06:17 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1000
# endif

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strndup(char *str, int n);
char	*ft_strchr(char *str, char c);
char	*ft_strstock(char *s1, char *s2, int param);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(char *str);

#endif