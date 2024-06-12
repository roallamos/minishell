/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:47:55 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/22 14:36:28 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	node = *lst;
	while (node)
	{
		next = node->next;
		ft_lstdelone(node, del);
		node = next;
	}
	*lst = NULL;
}

//int main(void)
//{
//	t_list	*new;
//	t_list	*first;
//
//	first = NULL;
//	while(ft_lstsize(first) != 3)
//	{		
//		new = ft_lstnew("hola");
//		ft_lstadd_back(&first, new);
//	}
//	while (first)
//	{
//		printf("%s\n", first->content);
//		first = first->next;
//	}
//	return (0);
//}
