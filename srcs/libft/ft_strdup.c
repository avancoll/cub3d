/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:04:28 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/04 01:04:34 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * (ft_strlen((char *)str) + 1));
	if (!ptr)
		return (NULL);
	if (str)
		ft_memcpy(ptr, (char *)str, ft_strlen((char *)str));
	ptr[ft_strlen((char *)str)] = 0;
	return (ptr);
}
