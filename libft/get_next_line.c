/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:27:49 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/12 09:02:35 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*null_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		len;

	if (!s2)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		len = (int)ft_strlen(s1);
	else
		len = 0;
	s = (char*)malloc(sizeof(char) * (len + ft_strlen(s2) + 1));
	if (s == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		while (*s1 != '\0')
			s[i++] = *s1++;
	}
	while (*s2 != '\0')
		s[i++] = *s2++;
	s[i] = '\0';
	return (s);
}

int		read_file(int fd, t_fds **fds)
{
	char	buffer[BUFF_SIZE + 1];
	int		ret;
	t_fds	*ptr;

	ptr = *fds;
	ft_bzero(buffer, BUFF_SIZE + 1);
	ret = 0;
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		ptr->str = null_strjoin(ptr->str, buffer);
		if (ft_strchr(ptr->str, '\n') != NULL)
			break ;
	}
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	int				i;
	static	t_fds	fds1[50];
	t_fds			*tmp;

	tmp = &(fds1[fd % 50]);
	i = 0;
	if (fd < 0 || !line)
		return (-1);
	if (read_file(fd, &tmp) < 0)
		return (-1);
	if (!tmp->str || tmp->str[i] == '\0')
		return (0);
	while (tmp->str[i] != '\n' && tmp->str[i] != '\0')
		i++;
	*line = ft_strsub(tmp->str, 0, i);
	tmp->str += i;
	if (*tmp->str != '\0')
		tmp->str++;
	return (1);
}
