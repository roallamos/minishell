/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:40:18 by migumore          #+#    #+#             */
/*   Updated: 2024/09/16 10:39:37 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	in_out_last(int *in, int *out, char **args)
{
	int	i;

	i = 0;
	*in = 0;
	*out = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<"))
			*in = 1;
		else if (ft_strcmp(args[i], "<<"))
			*in = 2;
		else if (ft_strcmp(args[i], ">"))
			*out = 1;
		else if (ft_strcmp(args[i], ">>"))
			*out = 2;
		i++;
	}
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
		{
			if (!ft_strcmp(args[i], "<<"))
				redir[j++] = ft_strjoin(args[i + 1], "\n");
			else
				redir[j++] = ft_strdup(args[i + 1]);
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
	in_out_last(&list->in_flag, &list->out_flag, list->args);
	expansor(list->args, data);
	list->outfile = ft_redir(list->args, ">");
	list->infile = ft_redir(list->args, "<");
	list->heredoc = ft_redir(list->args, "<<");
	list->append = ft_redir(list->args, ">>");
	list->args = ft_args(list->args);
	list->fd_infile = 0;
	list->fd_heredoc = 0;
	list->fd_outfile = 0;
	list->fd_append = 0;
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
