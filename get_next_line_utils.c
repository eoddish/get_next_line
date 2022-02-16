/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:56:15 by eoddish           #+#    #+#             */
/*   Updated: 2021/01/16 21:42:42 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_create_list(t_list **lst, void *content)
{
	t_list	*newelem;
	t_list	*back;

	if (!(newelem = (t_list *)malloc(sizeof(t_list))))
		return (-1);
	if (!(newelem->content = malloc(sizeof(char) * BUFFER_SIZE)))
		return (-1);
	ft_bzero(newelem->content, BUFFER_SIZE);
	ft_strncpy(newelem->content, content, BUFFER_SIZE);
	newelem->next = NULL;
	if (!*lst)
		*lst = newelem;
	else
	{
		back = *lst;
		while (back->next)
			back = back->next;
		back->next = newelem;
	}
	return (0);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *clear;
	t_list *temp;

	clear = *lst;
	while (clear != NULL)
	{
		temp = clear->next;
		(*del)(clear->content);
		(*del)(clear);
		clear = temp;
	}
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*t;

	if (s)
	{
		t = (char *)s;
		i = 0;
		while (i < n)
			t[i++] = '\0';
	}
}

void	ft_strncpy(char *dst, char *src, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

int		has_newline(char *buf, int n)
{
	while (n < BUFFER_SIZE)
	{
		if (buf[n] == '\n' || buf[n] == '\0')
			return (n);
		n++;
	}
	return (-1);
}
