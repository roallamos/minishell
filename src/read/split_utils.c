/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:29 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/09 12:15:31 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	advance_tokkens(const char *command, int *i, int *args)
{
	(*args)++;
	while (ft_istoken(command[*i]))
	{
		(*i)++;
		if (!ft_istoken(command[*i]))
		{
			(*i)--;
			break ;
		}
	}
}

static void	advance(const char *command, int *i, int *args, t_data *data)
{
	(*args)++;
	while ((command[*i] && !ft_istoken(command[*i])
			&& !ft_isspace(command[*i]))
		|| (data->d_quote || data->s_quote))
		set_quotes(command[(*i)++], &data->d_quote, &data->s_quote);
	if (ft_istoken(command[*i]))
		(*i)--;
}

int	args_nb(const char *command, t_data *data)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	if (only_spaces(command))
		return (1);
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			set_quotes(command[i], &data->d_quote, &data->s_quote);
			if ((data->d_quote || data->s_quote)
				&& command[i] == command[i + 1])
				args++;
		}
		else if (ft_istoken(command[i]) && !data->d_quote && !data->s_quote)
			advance_tokkens(command, &i, &args);
		else if (!ft_isspace(command[i]))
			advance(command, &i, &args, data);
		if (command[i])
			i++;
	}
	return (args);
}
