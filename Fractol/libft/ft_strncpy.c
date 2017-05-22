/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 14:11:29 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/14 14:11:30 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		end;

	i = 0;
	end = 0;
	while (i < len)
	{
		if (src[i] != '\0' && end != 1)
			dst[i] = src[i];
		else
		{
			dst[i] = 0;
			end = 1;
		}
		i++;
	}
	return (dst);
}
