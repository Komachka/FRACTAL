/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 15:54:05 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/22 11:11:26 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;
	size_t	ll;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	res = (char *)big;
	if (!big || !little)
		res[0] = 0;
	i = 0;
	ll = (int)ft_strlen(little);
	while (i + ll <= len && res[i])
	{
		j = 0;
		while (res[i + j] == little[j])
		{
			if (j == ll - 1)
				return (res + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
