/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 14:43:54 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/19 14:45:01 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static int	count_words(const char *str, char c)
{
	int		s;

	while (*str != '\0' && *str == c)
		++str;
	if (*str != '\0')
		s = 1;
	else
		s = 0;
	while (*str != '\0')
	{
		if (str[0] == c && str[1] && str[1] != c)
			s++;
		str++;
	}
	return (s);
}

char		**ft_strsplit(char const *str, char c)
{
	char	**arr;
	char	*b;
	int		words;

	if (!str || !c)
		return (NULL);
	words = count_words(str, c);
	if ((arr = (char **)malloc(sizeof(char*) * words + 1)) == NULL)
		return (NULL);
	b = (char *)str;
	while (*str != '\0')
	{
		if (*str == c)
		{
			if (b != str)
				*(arr++) = ft_strsub(b, 0, str - b);
			b = (char*)str + 1;
		}
		str++;
	}
	if (b != str)
		*(arr++) = ft_strsub(b, 0, str - b);
	*arr = NULL;
	return (arr - words);
}
