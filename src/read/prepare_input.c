/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:40:18 by migumore          #+#    #+#             */
/*   Updated: 2024/09/16 17:57:40 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirection_type(t_docs *redir, char *args, int pos)
{
	if (!ft_strcmp(args, "<"))
		redir[pos].flag = 0;
	if (!ft_strcmp(args, "<<"))
		redir[pos].flag = 1;
	if (!ft_strcmp(args, ">"))
		redir[pos].flag = 2;
	if (!ft_strcmp(args, ">>"))
		redir[pos].flag = 3;
}

char	**ft_args(char **args)
{
	int		i;
	int		j;
	int		nb;
	char	**ret;

	i = 0;
	j = 0;
	nb = 0;
	while (args[i])
	{
		if (!(!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">")
				|| !ft_strcmp(args[i], "<<") || !ft_strcmp(args[i], ">>")))
			nb++;
		i++;
	}
	ret = ft_calloc((nb + 1), sizeof(char *));
	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">")
			|| !ft_strcmp(args[i], "<<") || !ft_strcmp(args[i], ">>"))
			i += 2;
		else
			ret[j++] = ft_strdup(args[i++]);
	}
	ft_free_array(args);
	return (ret);
}

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

t_docs	*ft_redir(char **args)
{
	int		i;
	int		j;
	int		nb;
	t_docs	*redir;

	i = 0;
	j = 0;
	nb = nb_tokens(args, ">");
	nb += nb_tokens(args, ">>");
	nb += nb_tokens(args, "<<");
	nb += nb_tokens(args, "<");
	if (nb == 0)
		return (NULL);
	redir = ft_calloc(nb + 1, sizeof(t_docs *));
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], "<<") || !ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>"))
		{
			redir[j].doc = ft_strdup(args[i + 1]);
			redirection_type(redir, args[i], j);
			j++;
		}
		i++;
	}	
	return (redir);
}

t_cmd	*ft_new_node(char *commands, t_data *data)
{
	t_cmd	*list;

	(void) data;
	list = ft_calloc(1, sizeof(t_cmd));
	list->cmd = NULL;
	list->args = ft_split_args(commands);
//	in_out_last(&list->in_flag, &list->out_flag, list->args);
	list->docs = ft_redir(list->args);
	expansor(list->args, data);
	/*list->outfile = ft_redir(list->args, ">");
	list->infile = ft_redir(list->args, "<");
	list->heredoc = ft_redir(list->args, "<<");
	list->append = ft_redir(list->args, ">>");
	list->args = ft_args(list->args);*/
	list->next = NULL;
	return (list);
}

t_cmd	*ft_prepare_list(t_data *data)
{
	t_cmd	*list;
	int		i;

	i = 0;
	list = NULL;
	while (data->commands && data->commands[i])
	{
		ft_lstcmdadd_back(&list, ft_new_node(data->commands[i], data));
		i++;
	}
	data->num_commands = i;
	return (list);
}
