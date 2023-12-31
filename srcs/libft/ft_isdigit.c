/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:52:41 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/04 14:36:06 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}
