/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:40:18 by migumore          #+#    #+#             */
/*   Updated: 2024/07/09 17:54:56 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	expansor(char **args)
// {
// 	int i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		if (args[i][0] && args[i][0] == '$')
// 	//		expand_var();
		
// 	}
// }

int	nb_tokens(char **args, char *c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], c))
			nb++;
		i++;
	}
	return (nb);
}

char	**ft_redir(char **args, char *token)
{
	int		i;
	int		j;
	int		nb;
	char	**redir;

	i = 0;
	j = 0;
	nb = nb_tokens(args, token);
	if (nb == 0)
		return (NULL);
	redir = ft_calloc(nb + 1, sizeof(char *));
	while (args[i])
	{
		if (!ft_strcmp(args[i], token))
			redir[j++] = ft_strdup(args[i + 1]);
		i++;
	}
	return (redir);
}

t_cmd	*ft_new_node(char *commands)
{
	t_cmd	*list;

	list = ft_calloc(1, sizeof(t_cmd));
	list->cmd = NULL;
	list->args = ft_split_args(commands, ' '); // aqui es donde hay que modificar el split y llamar al expansor
	//expansor(list->args);
	list->outfile = ft_redir(list->args, ">");
	list->infile = ft_redir(list->args, "<");
	list->heredock = ft_redir(list->args, "<<");
	list->append = ft_redir(list->args, ">>");
	list->next = NULL;
	return (list);
}

t_cmd	*ft_prepare_list(t_data *data)
{
	t_cmd	*list;
	int		i;

	i = 0;
	list = NULL;
	while (data->commands[i])
	{
		ft_lstcmdadd_back(&list, ft_new_node(data->commands[i]));
		i++;
	}
	data->num_commands = i;
	return (list);
}
