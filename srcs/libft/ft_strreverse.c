/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:55:29 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/10 19:07:18 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strreverse(char *str)
{
	size_t	len;
	size_t	i;
	char	swap;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str && i < len)
	{
		swap = str[i];
		str[i] = str[len];
		str[len] = swap;
		i++;
		len--;
	}
}
