/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 09:27:22 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/14 13:50:32 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int					i;
	const unsigned char *p1;
	const unsigned char *p2;

	p1 = s1;
	p2 = s2;
	i = 0;
	while (n--)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		else
			i++;
	}
	return (0);
}
