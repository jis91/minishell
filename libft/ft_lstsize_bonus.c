/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:59:47 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 11:59:55 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	t_list	*list;
	t_list	*node;
	char	*str;
	char	*append;
	int	len;

	len = 0;
	append = "You are beautiful";
	str = "Hello World!";
	node = ft_lstnew(append);
	list = ft_lstnew(str);
	ft_lstadd_front(&list, node);
	len = ft_lstsize(list);
	printf("%i, is list length\n", len);
	t_list	*tmp;
	tmp = list;
	while (tmp)
	{
		printf("Node content is : %s\n",(char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}*/
