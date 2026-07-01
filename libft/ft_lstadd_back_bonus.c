/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:01:28 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 16:09:22 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
/*
int	main(void)
{
	t_list	*list;
	t_list	*msg;
	t_list	*tmp;
	char	*test;
	char	*test1;
	
	test = "Hello";
	test1 = "World";
	list = ft_lstnew(test);
	msg = ft_lstnew(test1);
	ft_lstadd_back(&list, msg);
	tmp = list;
	while (tmp)
	{	
		printf("Node content : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}*/
