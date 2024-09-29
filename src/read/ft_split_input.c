/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:47:13 by migumore          #+#    #+#             */
/*   Updated: 2024/09/29 19:37:23 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static char	**copy_pipes(int pipes, char *input)
{
	int	i;
	int	j;
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

char	**split_pipes(char *input)
{
	char	**ret;
	int		pipes;
	int		i;
	int		j;

	i = 0;
	j = 0;
	pipes = ft_nb_pipes(input);
	if (pipes == 0)
	{
		ret = ft_calloc(pipes + 2, sizeof(char *));
		ret[0] = ft_strdup(input);
		free(input);
		return (ret);
	}
	else
		ret = copy_pipes(pipes, input);
	free(input);
	return (ret);
}

char	**ft_split_input(char *input)
{
	char	**ret;

	ret = split_pipes(input);
	return (ret);
}
