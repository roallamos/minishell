/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:37:39 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/17 12:26:49 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isredir(char *args)
{
	if (!ft_strcmp(args, "<") || !ft_strcmp(args, ">")
		|| !ft_strcmp(args, "<<") || !ft_strcmp(args, ">>"))
		return (1);
	return (0);
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

int	nb_redir(char **args)
{
	int	nb;

	nb = nb_tokens(args, ">");
	nb += nb_tokens(args, ">>");
	nb += nb_tokens(args, "<<");
	nb += nb_tokens(args, "<");
	return (nb);
}

void	redirection_type(t_docs *redir, char *args, int pos)
{
	if (!ft_strcmp(args, "<"))
		redir[pos].flag = INFILE;
	else if (!ft_strcmp(args, "<<"))
		redir[pos].flag = HEREDOC;
	else if (!ft_strcmp(args, ">"))
		redir[pos].flag = OUTFILE;
	else if (!ft_strcmp(args, ">>"))
		redir[pos].flag = APPEND;
}

void	fill_redir_struct(t_docs *redir, char **args, int i, int j)
{
	redir[j].doc = ft_strdup(args[i + 1]);
	redirection_type(redir, args[i], j);
	redir[j].fd = -1;
	if (args[i + 1] && args[i + 1][0] && args[i + 1][0] == '"')
		redir[j].exp = 0;
	else
		redir[j].exp = 1;
}
