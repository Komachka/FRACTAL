/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 15:35:24 by kstorozh          #+#    #+#             */
/*   Updated: 2016/12/19 15:37:31 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ptr;

	if ((ptr = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		ptr->content_size = 0;
		ptr->content = NULL;
	}
	else
	{
		if ((ptr->content = malloc(content_size)) == NULL)
			return (NULL);
		ft_memcpy(ptr->content, content, content_size);
		ptr->content_size = content_size;
	}
	ptr->next = NULL;
	return (ptr);
}
