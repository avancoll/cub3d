/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:27:35 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/04 13:27:43 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	nb;
	long	neg;

	nb = 0;
	neg = 1;
	while (str && *str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (str && (*str == '+' || *str == '-'))
		if (*str++ == '-')
			neg = -1;
	while (str && ft_isdigit(*str))
	{
		nb = nb * 10 + *str++ - '0';
		if (nb < 0 && neg == 1)
			return (-1);
		if (nb < 0 && neg == -1)
			return (0);
	}
	return (nb * neg);
}
