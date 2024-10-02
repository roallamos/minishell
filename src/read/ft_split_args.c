/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:18:15 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/02 10:25:44 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	advance_tokkens(const char *command, int *i, int *args)
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

int	only_spaces(const char *command)
{
	int	i;

	i = 0;
	while (ft_isspace(command[i]))
	{
		i++;
		if (!command[i])
			return (1);
	}
	return (0);
}

void	non_sei(const char *command, int *i, int *args, t_data *data)
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
			non_sei(command, &i, &args, data);
		if (command[i])
			i++;
	}
	return (args);
}

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

void	move_quotes(char **args, int i, int *j, char quotes)
{
	if (!quotes || quotes == args[i][*j])
	{
		ft_memmove(&args[i][*j], &args[i][*j + 1],
			ft_strlen(&args[i][*j]));
		if (args[i][*j])
			(*j)--;
	}
}

void	remove_quotes(char **args, int f)
{
	int		i;
	int		j;
	char	quotes;

	quotes = 0;
	i = -1;
	while (args && args[++i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '"' || args[i][j] == '\'')
			{
				if (!quotes)
					quotes = args[i][j];
				else if (quotes == args[i][j])
					quotes = 0;
				move_quotes(args, i, &j, quotes);
			}
			if ((j >= 0 && args[i][j]) || j == -1)
				j++;
		}
		if (f)
			break ;
	}
}

char	**ft_split_args(char *command, t_data *data)
{
	char	**ret;
	int		nb;

	data->d_quote = 0;
	data->s_quote = 0;
	nb = args_nb(command, data);
	if (!nb)
		return (NULL);
	ret = ft_calloc(nb + 1, sizeof(char *));
	data->s_quote = 0;
	data->d_quote = 0;
	ft_cut_cmd(command, ret, data);
	ret = trim_spaces(ret);
	return (ret);
}
