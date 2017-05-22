/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 14:40:22 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/20 18:07:07 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *in)
{
	int				i;
	unsigned int	res;
	int				minus;
	int				plus;

	i = 0;
	res = 0;
	minus = 1;
	plus = 1;
	while (in[i] != '\0' && (in[i] == ' ' ||
in[i] == '\t' || in[i] == '\f' || in[i] == '\v' ||
in[i] == '\n' || in[i] == '+' || in[i] == '-' || in[i] == '\r'))
	{
		if (minus == -1 || plus == 0)
			return (0);
		if (in[i] == '-')
			minus = -1;
		if (in[i] == '+')
			plus = 0;
		i++;
	}
	while (in[i] >= '0' && in[i] <= '9')
		res = res * 10 + in[i++] - '0';
	return ((int)(res * minus));
}
