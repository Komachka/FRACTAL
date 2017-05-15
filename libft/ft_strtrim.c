/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 19:34:36 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/20 09:17:00 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strtrim(char const *s)
{
	int		b;
	int		e;
	char	*str;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	b = 0;
	e = (int)ft_strlen(s) - 1;
	i = 0;
	while (s[b] == ' ' || s[b] == '\n' || s[b] == '\t')
		b++;
	while (s[e] == ' ' || s[e] == '\n' || s[e] == '\t')
		e--;
	if ((size = e - b + 1) <= 0)
		size = 0;
	if ((str = (char*)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	while (b <= e)
		str[i++] = s[b++];
	str[i] = '\0';
	return (str);
}
