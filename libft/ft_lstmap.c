/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:15:51 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/19 16:44:16 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ptr;
	t_list	*nlst;

	nlst = ft_lstnew(lst->content, lst->content_size);
	if (nlst == NULL)
		return (NULL);
	nlst = f(lst);
	ptr = nlst;
	while (lst->next != NULL)
	{
		ptr->next = f(lst->next);
		ptr = ptr->next;
		lst = lst->next;
	}
	return (nlst);
}
