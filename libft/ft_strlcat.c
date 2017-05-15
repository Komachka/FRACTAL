/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:14:21 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/19 14:43:13 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	dst_len;

	len = 0;
	while (dst[len] != '\0' && len < size)
		len++;
	dst_len = len;
	while (src[len - dst_len] != '\0' && len < size - 1)
	{
		dst[len] = src[len - dst_len];
		len++;
	}
	if (dst_len < size)
		dst[len] = '\0';
	return (dst_len + ft_strlen(src));
}
