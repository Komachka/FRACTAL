/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:34:06 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/19 08:53:23 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*swap(char *str)
{
	int		i;
	char	tmp;

	i = 0;
	tmp = 0;
	while (i < (int)ft_strlen(str) / 2)
	{
		tmp = str[i];
		str[i] = str[ft_strlen(str) - 1 - i];
		str[ft_strlen(str) - 1 - i] = tmp;
		i++;
	}
	return (str);
}

static int	count_size(int i)
{
	int				count;
	unsigned int	x;

	count = 0;
	x = i;
	if (i == 0)
		count++;
	if (i < 0)
	{
		count++;
		x = -i;
	}
	while (x > 0)
	{
		count++;
		x = x / 10;
	}
	return (count);
}

char		*ft_itoa(int i)
{
	char			*word;
	unsigned int	nb;
	int				count;
	int				flag;

	count = 0;
	flag = 0;
	nb = i;
	if ((word = (char*)malloc(sizeof(char) * (count_size(i) + 1))) == NULL)
		return (NULL);
	if (i == 0)
		word[count++] = '0';
	if (i < 0)
		nb = -i;
	while (nb > 0 && i != 0)
	{
		word[count++] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (i < 0)
		word[count++] = '-';
	word[count] = '\0';
	return (swap(word));
}
