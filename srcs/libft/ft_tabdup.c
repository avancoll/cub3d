/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:21:21 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/11 15:16:59 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	double_free(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i++] = NULL;
	}
	free(tab);
	tab = NULL;
}

char	**ft_tabdup(char **tab)
{
	size_t	size;
	char	**new_tab;

	size = 0;
	if (!tab)
		return (NULL);
	while (tab[size])
		size++;
	new_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_tab)
		return (NULL);
	ft_bzero(new_tab, size + 1);
	size = 0;
	while (tab[size])
	{
		new_tab[size] = ft_strdup(tab[size]);
		if (!new_tab[size])
		{
			double_free(new_tab);
			return (NULL);
		}
		size++;
	}
	new_tab[size] = NULL;
	return (new_tab);
}
