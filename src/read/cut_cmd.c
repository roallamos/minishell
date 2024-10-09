/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:38 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/09 12:15:40 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*copy_quotes(char *command, int *i, t_data *data, char *start)
{
	while (command[*i] && (data->d_quote || data->s_quote))
	{
		set_quotes(command[++(*i)], &data->d_quote, &data->s_quote);
		if (!data->d_quote && !data->s_quote && (command[*i + 1] == '\''
				|| command[*i + 1] == '"'))
			set_quotes(command[++(*i)], &data->d_quote, &data->s_quote);
	}
	return (ft_strndup(start, &command[(*i)++] - start + 1));
}

char	*copy_arg(char *command, int *i, char *start)
{
	while (command[*i] && !ft_isspace(command[*i])
		&& !ft_istoken(command[*i]))
		(*i)++;
	return (ft_strndup(start, &command[*i] - start));
}

void	ft_cut_cmd(char *command, char **ret, t_data *data)
{
	int		i;
	int		j;
	char	*start;

	i = 0;
	j = 0;
	if (only_spaces(command))
		ret[j] = ft_strdup(command);
	while (command[i])
	{
		start = &command[i];
		set_quotes(command[i], &data->d_quote, &data->s_quote);
		if (ft_isspace(command[i]) && !data->d_quote && !data->s_quote)
			i++;
		else if (ft_istoken(command[i]) && !data->d_quote && !data->s_quote)
		{
			while (ft_istoken(command[i]))
				i++;
			ret[j++] = ft_strndup(start, &command[i] - start);
		}
		else if (data->d_quote || data->s_quote)
			ret[j++] = copy_quotes(command, &i, data, start);
		else
			ret[j++] = copy_arg(command, &i, start);
	}
}
