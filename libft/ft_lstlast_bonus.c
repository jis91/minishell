/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:02:33 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 15:48:55 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *list)
{
	t_list	*tmp;

	if (!list)
		return (NULL);
	tmp = list;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
/*
int	main(void)
{
	t_list	*list;
	t_list	*append;
	t_list	*last;
	char	*msg;
	char	*add;

	msg = "Hello";
	add = "World";
	list = ft_lstnew(add);
	append = ft_lstnew(msg);
	ft_lstadd_front(&list, append);
	last = ft_lstlast(list);
	printf("%s\n", (char *)last->content);
	return (0);
}*/
