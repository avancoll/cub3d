/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:05:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/04 01:06:00 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*str;
	size_t			i;

	i = -1;
	dest = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (!n || dest == src)
		return (dest);
	while (dest && str && ++i < n)
		dest[i] = str[i];
	return (dest);
}
