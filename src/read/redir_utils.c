/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:37:39 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/30 17:41:43 by rodralva         ###   ########.fr       */
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
		redir[pos].flag = HERE_DOC;
	else if (!ft_strcmp(args, ">"))
		redir[pos].flag = OUTFILE;
	else if (!ft_strcmp(args, ">>"))
		redir[pos].flag = APPEND;
}
