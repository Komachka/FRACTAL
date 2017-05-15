/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 15:17:42 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/14 14:13:07 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *big, const char *little)
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
		return (res);
	while (big[i] != 0)
	{
		j = 0;
		while (res[i + j] == little[j])
		{
			if (j == ll - 1)
				return (res + i);
			j++;
		}
		i++;
	}
	return (0);
}
