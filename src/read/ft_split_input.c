/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:47:13 by migumore          #+#    #+#             */
/*   Updated: 2024/10/21 16:19:56 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_nb_pipes(char *input, t_data *data)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	set_quotes(input[i], &data->d_quote, &data->s_quote);
	while (input[i])
	{
		if (input[i] == '|' && !data->d_quote && !data->s_quote)
			pipes++;
		i++;
		set_quotes(input[i], &data->d_quote, &data->s_quote);
	}
	return (pipes);
}

static char	**copy_pipes(int pipes, char *input)
{
	int		i;
	int		j;
	char	*start;
	char	**ret;

	i = 0;
	j = 0;
	start = input;
	ret = ft_calloc(pipes + 2, sizeof(char *));
	while (input[i])
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
	return (ret);
}

char	**split_pipes(char *input, t_data *data)
{
	char	**ret;
	int		pipes;

	pipes = ft_nb_pipes(input, data);
	if (pipes == 0)
	{
		ret = ft_calloc(pipes + 2, sizeof(char *));
		ret[0] = ft_strdup(input);
		return (ret);
	}
	else
		ret = copy_pipes(pipes, input);
	return (ret);
}

char	**ft_split_input(char *input, t_data *data)
{
	char	**ret;

	ret = split_pipes(input, data);
	return (ret);
}
