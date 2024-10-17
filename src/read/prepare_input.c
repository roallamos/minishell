/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:40:18 by migumore          #+#    #+#             */
/*   Updated: 2024/10/17 16:05:24 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		if (!ft_isredir(args[i]))
			nb++;
		i++;
	}
	ret = ft_calloc((nb + 1), sizeof(char *));
	i = 0;
	while (args[i])
	{
		if (ft_isredir(args[i]))
			i += 2;
		else
			ret[j++] = ft_strdup(args[i++]);
	}
	ft_free_array((void **)args);
	return (ret);
}

t_docs	*ft_redir(char **args)
{
	int		i;
	int		j;
	int		nb;
	t_docs	*redir;

	i = 0;
	j = 0;
	if (!args)
		return (NULL);
	nb = nb_redir(args);
	if (nb == 0)
		return (NULL);
	redir = ft_calloc(nb + 1, sizeof(t_docs));
	while (args[i])
	{
		if (ft_isredir(args[i]))
		{
			fill_redir_struct(redir, args, i, j);
			j++;
		}
		i++;
	}
	return (redir);
}

char	**exclude_redir(char **args)
{
	int		i;
	int		j;
	int		nb;
	char	**ret;

	i = 0;
	j = 0;
	if (!args)
		return (NULL);
	while (args[i])
		i++;
	nb = nb_redir(args);
	nb = i - nb;
	ret = ft_calloc(nb + 1, sizeof(char *));
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<") && ft_strcmp(args[i], "<<")
			&& ft_strcmp(args[i], ">") && ft_strcmp(args[i], ">>"))
			ret[j++] = ft_strdup(args[i++]);
		else
			i += 2;
	}
	ft_free_array((void **)args);
	return (ret);
}

t_cmd	*ft_new_node(char *commands, t_data *data)
{
	t_cmd	*list;
	int		i;

	i = 0;
	(void) data;
	list = ft_calloc(1, sizeof(t_cmd));
	list->cmd = NULL;
	list->stop_exec = 0;
	list->args = ft_split_args(commands, data);
	list->docs = ft_redir(list->args);
	list->args = exclude_redir(list->args);
	full_expansor(list->args, data);
	remove_quotes(list->args, 0);
	while (list->docs && list->docs[i].doc)
	{
		list->docs[i].exp = delimiter_expansor(&list->docs[i].doc, data);
		remove_quotes(&list->docs[i++].doc, 1);
	}
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
	ft_free_array((void **)data->commands);
	data->num_commands = i;
	return (list);
}
