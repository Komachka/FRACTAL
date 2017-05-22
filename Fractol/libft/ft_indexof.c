/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 18:27:04 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/22 11:30:34 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_indexof(const char *big, const char *little)
{
	int		i;
	int		j;
	int		ll;
	char	*res;

	res = (char *)big;
	i = 0;
	ll = 0;
	while (little[ll] != '\0')
		ll++;
	if (ll == 0)
		return (0);
	while (big[i] != 0)
	{
		j = 0;
		while (res[i + j] == little[j])
		{
			if (j == ll - 1)
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}
