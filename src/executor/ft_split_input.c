/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:47:13 by migumore          #+#    #+#             */
/*   Updated: 2024/06/22 16:08:19 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	process_quotes(t_data *data)
{
	data->quote = *data->pos++;
	data->start = data->pos;
	if (*data->start == data->quote)
	{
		data->pos++;
		data->start++;
		return ;
	}
	while (*data->pos && *data->pos != data->quote)
		data->pos++;
}

static int	proces_hashtag(t_data *data)
{
	while (*data->pos)
		data->pos++;
	data->args[data->size] = ft_calloc(1, 8);
	return (0);
}

static int	process(t_data *data)
{
	data->start = data->pos;
	if (*data->pos == '#')
		return (proces_hashtag(data));
	else if (*data->pos == '"' || *data->pos == '\'')
		process_quotes(data);
	else
	{
		while (*data->pos && *data->pos != ' ')
			data->pos++;
	}
	if (data->size >= data->cap - 1)
	{
		data->args = (char **)ft_realloc(data->args, data->size, data->cap * 2);
		if (!data->args)
			return (1);
	}
	data->args[data->size] = ft_strndup(data->start, data->pos - data->start);
	if (!data->args[data->size])
		return (1);
	data->size++;
	if (*data->pos)
		data->pos++;
	return (0);
}

char	**ft_split_input(const char *command, t_data *data)
{
	data->cap = 10;
	data->size = 0;
	data->args = (char **)malloc(data->cap * sizeof(char *));
	if (!data->args)
		return (NULL);
	data->pos = command;
	while (1)
	{
		while (*data->pos && *data->pos == ' ')
			data->pos++;
		if (*data->pos == '\0')
		{
			data->args[data->size] = ft_calloc(1, 1);
			data->size++;
			break ;
		}
		if (process(data) == 1)
			return (NULL);
	}
	data->args[data->size] = NULL;
	return (data->args);
}
