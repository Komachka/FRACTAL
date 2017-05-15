/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 09:42:36 by kstorozh          #+#    #+#             */
/*   Updated: 2017/04/26 18:39:20 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 3

# include "libft.h"

typedef	struct		s_fds
{
	int				fd;
	char			*str;
}					t_fds;

int					get_next_line(const int fd, char **line);
#endif
