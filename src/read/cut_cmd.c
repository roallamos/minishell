/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:38 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/15 22:49:58 by rodralva         ###   ########.fr       */
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
	int	d_quotes;
	int	s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	while ((command[*i] && !ft_isspace(command[*i])
			&& !ft_istoken(command[*i])) || (d_quotes || s_quotes))
	{
		set_quotes(command[*i], &d_quotes, &s_quotes);
		(*i)++;
	}
	return (ft_strndup(start, &command[*i] - start));
}

void	ft_cut_cmd(char *command, char **ret)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	j = 0;
	if (only_spaces(command))
		ret[j] = ft_strdup(command);
	while (command[i])
	{
		k = 0;
		while (ft_isspace(command[i]))
			i++;
		if (command[i] && !ft_istoken(command[i]))
			ret[j++] = copy_arg(command, &i, &command[i]);
		else if (command[i] && ft_istoken(command[i]))
		{
			while (ft_istoken(command[i + k]))
				k++;
			ret[j++] = ft_substr(command, i, k);
			i += k;
		}
	}
}

/*void	ft_cut_cmd(char *command, char **ret, t_data *data)
{
	int		i;
	int		j;
	char	*start;

	i = 0;
	j = 0;
	printf("caommand %s\n", command);
	if (only_spaces(command))
		ret[j] = ft_strdup(command);
	while (command && command[i])
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
			printf("1\n");
		}
		else if (data->d_quote || data->s_quote)
		{
			ret[j++] = copy_quotes(command, &i, data, start);
			printf("2\n");
		}
		else
		{
			ret[j++] = copy_arg(command, &i, start);
			printf("1\n");
		}
	}
}*/
