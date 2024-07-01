#include <minishell.h>

t_command_list	*ft_lstcmdlast(t_command_list *lst)
{

	while (lst && lst->next)
    {
		lst = lst->next;
    }
	return (lst);
}

void	ft_lstcmdadd_back(t_command_list **lst, t_command_list *new)
{
	t_command_list	*last;

	last = ft_lstcmdlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}
