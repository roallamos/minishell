/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:39:51 by migumore          #+#    #+#             */
/*   Updated: 2024/07/01 16:40:07 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*ft_lstcmdlast(t_cmd *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstcmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = ft_lstcmdlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}
