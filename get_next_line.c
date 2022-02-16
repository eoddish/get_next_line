/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:31:39 by eoddish           #+#    #+#             */
/*   Updated: 2021/01/17 15:45:36 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	ft_fill(char **line, char *previous, int off, t_list *move)
{
	int x;
	int j;
	int k;

	x = 0;
	while (has_newline(previous, off) != x + off && x + off < BUFFER_SIZE)
	{
		*(*line + x) = previous[x + off];
		x++;
	}
	k = 0;
	while (move)
	{
		j = 0;
		while (j < BUFFER_SIZE)
		{
			if (has_newline((char *)(move->content), 0) == j)
				break ;
			*(*line + j + k * BUFFER_SIZE + x) = ((char *)(move->content))[j];
			j++;
		}
		move = move->next;
		k++;
	}
}

char	*ft_prep(char *previous, int *off, t_list **lst, int fl)
{
	int		x;
	t_list	*move;

	move = *lst;
	if (move)
		while (move->next)
			move = move->next;
	x = 0;
	while (has_newline(previous, *off) != x + *off && x + *off < BUFFER_SIZE)
		x++;
	if (*lst)
	{
		ft_bzero(previous, BUFFER_SIZE);
		ft_strncpy(previous, move->content, BUFFER_SIZE);
		*off = has_newline(move->content, 0) + 1;
		ft_lstclear(lst, free);
	}
	else
		*off = *off + x + 1;
	if (*off == BUFFER_SIZE || (fl < BUFFER_SIZE && (*off > fl || *off == 0)))
	{
		*off = 0;
		ft_bzero(previous, BUFFER_SIZE);
	}
	return (previous);
}

int		ft_reading_in(t_list **lst, char **buf, int fd)
{
	int flag;
	int re;

	flag = 0;
	re = 1;
	ft_bzero(*buf, BUFFER_SIZE);
	while (re > 0)
	{
		flag = read(fd, *buf, BUFFER_SIZE);
		re = flag;
		if (ft_create_list(lst, *buf) == -1)
		{
			ft_lstclear(lst, free);
			free(*buf);
			return (-1);
		}
		if (has_newline(*buf, 0) >= 0)
			break ;
		ft_bzero(*buf, BUFFER_SIZE);
	}
	if (flag == -1)
		if (*buf)
			free(*buf);
	return (flag);
}

char	*ft_create_line(char **buf, char *previous, t_list *lst, int offset)
{
	int		size;
	char	*line;
	int		n;

	n = 0;
	size = 0;
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	if (n)
		size += BUFFER_SIZE * (n - 1);
	if (offset && has_newline(previous, offset) > -1)
		size += has_newline(previous, offset) - offset;
	else if (offset)
		size += BUFFER_SIZE - offset;
	size += has_newline(*buf, 0);
	if (!(line = (char *)malloc(size + 1)) && lst)
		ft_lstclear(&lst, free);
	ft_bzero(line, size + 1);
	if (*buf)
		free(*buf);
	return (line);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	static char	prev[BUFFER_SIZE];
	static int	off;
	t_list		*lst;
	static int	flag;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || !(buf = (malloc(BUFFER_SIZE))))
		return (-1);
	lst = 0;
	ft_bzero(buf, BUFFER_SIZE);
	if (has_newline(prev, off) == -1 || off == 0)
		if ((flag = ft_reading_in(&lst, &buf, fd)) < 0)
			return (-1);
	if (!(*line = ft_create_line(&buf, prev, lst, off)))
		return (-1);
	ft_fill(line, prev, off, lst);
	ft_strncpy(prev, (buf = ft_prep(prev, &off, &lst, flag)), BUFFER_SIZE);
	if (flag < BUFFER_SIZE && (off > flag || off == 0))
		return (0);
	if (flag == off)
	{
		off = 0;
		ft_bzero(prev, BUFFER_SIZE);
	}
	return (1);
}
