/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:18:15 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/21 15:16:01 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	args_nb(const char *command)
{
	int	i;
	int	args;
	int	s_quote = 0;
	int	d_quote = 0;

	i = 0;
	args = 0;
	while (ft_isspace(command[i]))
	{
		i++;
		if (!command[i])
			return (1);
	}
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			set_quotes(command[i], &d_quote, &s_quote);
			if ((d_quote || s_quote) && command[i] == command[i + 1])
				args++;
		}
		else if (ft_istoken(command[i]) && !d_quote && !s_quote)
		{
			args++;
			while (ft_istoken(command[i]))
			{
				i++;
				if (!ft_istoken(command[i]))
				{
					i--;
					break;
				}
			}
		//	printf("tokend+s\n");
		}
		else if (!ft_isspace(command[i]))
		{
			args++;
		//	printf("movida %s\n", &command[i]);
			while ((command[i] && !ft_istoken(command[i]) && !ft_isspace(command[i])) || (d_quote || s_quote))
			{
				set_quotes(command[i], &d_quote, &s_quote);
				i++;
			}
			if (ft_istoken(command[i]))
				i--;
		//	printf("resto\n");
		}
		if (command[i])
			i++;
	}
	return (args);
}

void	ft_cut_cmd(char *command, char **ret)
{
	int		i;
	int		j;
	int		s_quote;
	int		d_quote;
	char	*start;

	i = 0;
	j = 0;
	s_quote = 0;
	d_quote = 0;
	while (ft_isspace(command[i]))
	{
		i++;
		if (!command[i])
			ret[j] = ft_strdup(command);
	}
	while (command[i])
	{
		start = &command[i];
		set_quotes(command[i], &d_quote, &s_quote);
		if (ft_isspace(command[i]) && !d_quote && !s_quote)
			i++;
		else if (ft_istoken(command[i]) && !d_quote && !s_quote)
		{
			while (ft_istoken(command[i]))
				i++;
			ret[j++] = ft_strndup(start, &command[i] - start);
		//	printf("reet %s\n", ret[j - 1]);
		}
		else if (d_quote || s_quote)
		{
			while (command[i] && (d_quote || s_quote))
			{
				i++;
				set_quotes(command[i], &d_quote, &s_quote);
				if (!d_quote && !s_quote && (command[i + 1] == '\'' || command[i + 1] == '"'))
				{
					i++;
					set_quotes(command[i], &d_quote, &s_quote);
				}
			}
			ret[j++] = ft_strndup(start, &command[i++] - start + 1);
		}
		else
		{
			while (command[i] && !ft_isspace(command[i]) && !ft_istoken(command[i]))
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

void	remove_quotes(char **args, int f)
{
	int		i;
	int		j;
	char	quotes;

	quotes = 0;
	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])// un puto segfault que ya encontré y no se solucionar
		{
			if (args[i][j] == '"' || args[i][j] == '\'')
			{
				if (!quotes)
					quotes = args[i][j];
				else if (quotes == args[i][j])
					quotes = 0;
				if (!quotes || quotes == args[i][j])
				{
					ft_memmove(&args[i][j], &args[i][j + 1], ft_strlen(&args[i][j]));
					if (args[i][j])
						j--;
				}
			}
			if ((j >= 0 && args[i][j]) || j == -1)
				j++;
		}
		if (f)
			break;
		i++;
	}
}

char	**ft_split_args(char *command)
{
	char	**ret;
	int		nb;

	nb = args_nb(command);
	if (!nb)
		return (NULL);
	ret = ft_calloc(nb + 1, sizeof(char *));
	ft_cut_cmd(command, ret);
	ret = trim_spaces(ret);
	//remove_quotes(ret);
	return (ret);
}
