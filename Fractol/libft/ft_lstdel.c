/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 15:26:03 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/19 15:26:04 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;
	t_list *tmp;

	if (alst != NULL)
	{
		ptr = *alst;
		while (ptr != NULL)
		{
			tmp = ptr->next;
			ft_lstdelone(&ptr, del);
			ptr = tmp;
		}
	}
	*alst = NULL;
}
