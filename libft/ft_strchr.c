/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:17:02 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/17 14:51:46 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == c)
			return ((char *)s);
		else if (*s++ == '\0')
			return (NULL);
	}
}