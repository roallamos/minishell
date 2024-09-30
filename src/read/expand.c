/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:12:50 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/30 11:09:00 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	full_expansor(char **args, t_data *data)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	j = 0;
	data->d_quote = 0;
	data->s_quote = 0;
	while (args && args[++i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '"')
				set_quotes(args[i][j], &data->d_quote, &data->s_quote);
			else if (args[i][j] == '$' && (args[i][j + 1] == '"'
				|| args[i][j + 1] == '\'') && !data->d_quote && !data->s_quote)
				remove_dollar(args, i, &j, &flag);
			else if (args[i][j] == '$' && !data->s_quote
				&& args[i][j + 1] != '"' && args[i][j + 1] != '\'')
				args[i] = expand_var(data, args[i]);
			if ((j >= 0 && args[i][j]) || j == -1)
				j++;
		}
		j = 0;
	}
}

int	delimiter_expansor(char **args, t_data *data)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	data->d_quote = 0;
	data->s_quote = 0;
	flag = 1;
	if (args && args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '"')
				set_quotes(args[i][j], &data->d_quote, &data->s_quote);
			else if (args[i][j] == '$' && (args[i][j + 1] == '"'
				|| args[i][j + 1] == '\'') && !data->d_quote && !data->s_quote)
				remove_dollar(args, i, &j, &flag);
			if ((j >= 0 && args[i][j]) || j == -1)
				j++;
		}
		j = 0;
		i++;
	}
	return (flag);
}

void	heredock_expansor(char **args, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->d_quote = 0;
	data->s_quote = 0;
	while (args && args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '"')
				set_quotes(args[i][j], &data->d_quote, &data->s_quote);
			else if (args[i][j] == '$' && !data->s_quote
				&& args[i][j + 1] != '"' && args[i][j + 1] != '\'')
				args[i] = expand_var(data, args[i]);
			if ((j >= 0 && args[i][j]) || j == -1)
				j++;
		}
		j = 0;
		i++;
	}
}
