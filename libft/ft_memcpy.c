/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 11:37:02 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/14 13:51:08 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr;
	const char	*sp;
	int			i;

	ptr = dst;
	sp = src;
	i = 0;
	while (n--)
	{
		ptr[i] = sp[i];
		i++;
	}
	return (dst);
}
