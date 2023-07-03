/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:09:32 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/03 21:21:09 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	previous_reader(char *str, char **tmp, int mod)
{
	int		i;
	int		end;
	char	*ptr;

	i = ft_strlen(str);
	end = 0;
	if (mod == 0 && (!str || !*str))
		return (0);
	if (ft_strchr(str, '\n'))
		i = ft_strchr(str, '\n') - str;
	if (ft_strchr(str, '\n'))
		end = -1;
	ptr = ft_strndup(str, i + 1);
	ft_memmove(str, &str[i + (str[i] == '\n')], ft_strlen(&str[i
			+ (str[i] == '\n')]) + 1);
	if (mod == 0)
	{
		*tmp = ptr;
		return (end);
	}
	*tmp = ft_strstock(*tmp, ptr, 1);
	free(ptr);
	if (!str[0] && end != -1)
		end = 1;
	return (end);
}

static char	*ft_retrun_spec(char *tmp)
{
	size_t	i;

	i = 0;
	while (tmp && tmp[i])
		i++;
	if (!i)
		return (ft_strndup("", 0));
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	tmp_fd[OPEN_MAX][BUFFER_SIZE + 1];
	int			ret;
	char		*tmp;

	ret = 0;
	tmp = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (NULL);
	ret = previous_reader(&tmp_fd[fd][0], &tmp, 0);
	if (ret < 0)
		return (ft_retrun_spec(tmp));
	ret = 1;
	while (ret)
	{
		ret = read(fd, tmp_fd[fd], BUFFER_SIZE);
		tmp_fd[fd][ret] = '\0';
		if ((!ret && !ft_strlen(tmp)) || ret == -1)
			return (NULL);
		if (ret > 0)
			ret = previous_reader((char *)&tmp_fd[fd][0], &tmp, 1);
		if (ret <= 0)
			return (ft_retrun_spec(tmp));
	}
	return (NULL);
}
