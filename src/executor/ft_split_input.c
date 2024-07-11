/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:47:13 by migumore          #+#    #+#             */
/*   Updated: 2024/07/11 18:44:23 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*static void	process_tokens(t_data *data)
{
	data->start = data->pos++;
	while (ft_istoken(*data->pos))
		data->pos++;
}

static void	process_quotes(t_data *data)
{
	//data->start = data->pos;
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
	else if (ft_istoken(*data->pos))
		process_tokens(data);
	else
	{
		while (*data->pos && *data->pos != ' ' && !ft_istoken(*data->pos))
		{
			if (*data->pos == '"' || *data->pos == '\'')
				process_quotes(data);
			data->pos++;
		}
	}
	//else if (*data->pos == '"' || *data->pos == '\'')
	//	process_quotes(data);
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
}*/

int	ft_nb_pipes(char *input)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (input[i])
	{
		if (input[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

char	**split_pipes(char *input)
{
	char	**ret;
	char	*start;
	int		pipes;
	int		i;
	int		j;

	i = 0;
	j = 0;
	pipes = ft_nb_pipes(input);
	ret = ft_calloc(pipes + 2, sizeof(char *));
	if (pipes == 0)
	{
		ret[0] = ft_strdup(input);
		free(input);
		return (ret);
	}
	start = input;
	while(input[i])
	{
		if (input[i] == '|')
		{
			ret[j] = ft_strndup(start, &input[i] - start);
			j++;
			start = &input[i + 1];
		}
		i++;
	}
	ret[j] = ft_strndup(start, &input[i] - start + 1);
	free(input);
	return (ret);
}

char	**ft_split_input(char *input)
{
	char **ret;

	ret = split_pipes(input);
	return (ret);
}

