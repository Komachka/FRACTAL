/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:19:03 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/17 17:28:31 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*last;

	last = NULL;
	len = ft_strlen((char *)s);
	while (len != 0 && s[len] != c)
		len--;
	if (s[len] == c)
		last = ((char*)&s[len]);
	return (last);
}
