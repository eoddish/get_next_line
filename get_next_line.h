/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:09:47 by eoddish           #+#    #+#             */
/*   Updated: 2021/01/16 21:44:42 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

void				ft_bzero(void *s, size_t n);
int					get_next_line(int fd, char **line);
int					ft_create_list(t_list **lst, void *content);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_strncpy(char *dst, char *src, int n);
int					has_newline(char *buf, int n);
#endif
