/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:47:13 by migumore          #+#    #+#             */
/*   Updated: 2024/07/10 18:10:36 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	process_tokens(t_data *data)
{
	data->start = data->pos++;
	while (ft_istoken(*data->pos))
		data->pos++;
}

static void	process_quotes(t_data *data)
{
	data->start = data->pos;
	while(*data->pos == '\'' || *data->pos == '"')
	{
		data->quote = *data->pos;
		data->pos++;
		while (*data->pos && *data->pos != data->quote)
			data->pos++;
		if (*data->pos == data->quote)
			data->pos++;
		while(*data->pos && !ft_isspace(*data->pos))
			data->pos++;
	}
}

static int	proces_hashtag(t_data *data)
{
	while (*data->pos)
		data->pos++;
	data->commands[data->size] = ft_calloc(1, 8);
	return (0);
}

static int	process(t_data *data)
{
	data->start = data->pos;
	if (*data->pos == '#')
		return (proces_hashtag(data));
	else if (*data->pos == '"' || *data->pos == '\'')
		process_quotes(data);
	else if (ft_istoken(*data->pos))
		process_tokens(data);
	else
	{
		while (*data->pos && *data->pos != ' ' && !ft_istoken(*data->pos))
			data->pos++;
	}
	if (data->size >= data->cap - 1)
	{
		data->commands = (char **)ft_realloc(data->commands, data->size,
				data->cap * 2);
		if (!data->commands)
			return (1);
	}
	data->commands[data->size] = ft_strndup(data->start,
			data->pos - data->start);
	if (!data->commands[data->size])
		return (1);
	data->size++;
//	if (*data->pos)
//		data->pos++;
	return (0);
}

char	**ft_split_input(const char *command, t_data *data)
{
	data->cap = 10;
	data->size = 0;
	data->commands = (char **)malloc(data->cap * sizeof(char *));
	if (!data->commands)
		return (NULL);
	data->pos = command;
	while (1)
	{
		while (*data->pos && ft_isspace(*data->pos))
			data->pos++;
		if (*data->pos == '\0')
		{
			if (data->size == 0)
			{
				data->commands[data->size] = ft_calloc(1, 1);
				data->size++;
			}
			break ;
		}
		if (process(data) == 1)
			return (NULL);
	}
	data->commands[data->size] = NULL;
	return (data->commands);
}
