/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:12:08 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/21 21:12:35 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*ft_toupper_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = (char)ft_toupper(str[i]);
		i++;
	}
	return (str);
}

void	del_arrey(void **arrey, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (arrey[i] != NULL)
			free(arrey[i]);
		i++;
	}
	if (arrey != NULL)
		free(arrey);
}

void	swap(double *x1, double *x2)
{
	double	i;
	double	j;

	i = *x1;
	j = *x2;
	*x1 = j;
	*x2 = i;
}

double	to_radians(double degrees)
{
	return (degrees / 180.0 * M_PI);
}

int		what_fractal_is_it(char c)
{
	char f;

	f = c;
	if (f == 'J')
		return (JULIA);
	if (f == 'M')
		return (MALDEBROT);
	if (f == 'P')
		return (PYFAGOR);
	return (0);
}
