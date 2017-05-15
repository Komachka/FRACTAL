/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 11:03:31 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/17 13:48:05 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*ptrdst;
	char	*ptrsrc;

	ptrdst = (char *)dst;
	ptrsrc = (char *)src;
	if (ptrsrc < ptrdst)
	{
		ptrdst += n - 1;
		ptrsrc += n - 1;
		while (n > 0)
		{
			*ptrdst-- = *ptrsrc--;
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			*ptrdst++ = *ptrsrc++;
			n--;
		}
	}
	return (dst);
}
