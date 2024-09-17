/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:18:15 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/17 11:37:47 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	args_nb(const char *command)
{
	int		i;
	int		args;
	char	quote;
	int		f;

	i = 0;
	args = 0;
	quote = 0;
	f = 1;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			if (!quote)
				quote = command[i];
			else if (quote == command[i])
				quote = 0;
		}
		else if (ft_istoken(command[i]))
		{
			args++;
			while (ft_istoken(command[i]))
				i++;
			i--;
		}
		else if (!ft_isspace(command[i]) && f == 1)
		{
			args++;
			f = 0;
		}
		else if (ft_isspace(command[i]) && !quote)
			f = 1;
		i++;
	}
	return (args);
}

void	ft_cut_cmd(char *command, char **ret)
{
	int		i;
	int		j;
	char	quote;
	char	*start;

	i = 0;
	j = 0;
	quote = 0;
	while (command[i])
	{
		start = &command[i];
		while (ft_isspace(command[i]))
			i++;
		while (command[i] && (!ft_isspace(command[i]) || quote)) //aqui hacer la funcion de quotes
		{
			if (command[i] == '\'' || command[i] == '"')
			{
				if (!quote)
					quote = command[i];
				else if (quote == command[i])
					quote = 0;
			}
			i++;
		}
		ret[j++] = ft_strndup(start, &command[i] - start + 1);
		while (command[i] && ft_isspace(command[i]) && !ft_istoken(command[i]))
			i++;
		if (ft_istoken(command[i]))
		{
			start = &command[i];
			while (ft_istoken(command[i]) || ft_isspace(command[i]))
				i++;
			ret[j++] = ft_strndup(start, &command[i] - start);
		}
	}
}

char	**trim_spaces(char **args)
{
	int		i;
	char	**ret;

	i = 0;
	while (args[i])
		i++;
	ret = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (args[i])
	{
		ret[i] = ft_strtrim(args[i], " \t \n \f \r \v");
		i++;
	}
	ft_free_array(args);
	return (ret);
}

char	**ft_split_args(char *command)
{
	char	**ret;

	ret = ft_calloc(args_nb(command) + 1, sizeof(char *));
	ft_cut_cmd(command, ret);
	ret = trim_spaces(ret);
	return (ret);
}
