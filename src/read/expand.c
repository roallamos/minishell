/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:12:50 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/17 11:42:41 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_quotes(char c, int *d_quote, int *s_quote)
{
	if (c == '\'' && !*s_quote && !*d_quote)
		*s_quote = 1;
	else if (c == '\'' && *s_quote)
		*s_quote = 0;
	if (c == '"' && !*d_quote && !*s_quote)
		*d_quote = 1;
	else if (c == '"' && *d_quote)
		*d_quote = 0;
}

char	*ft_replace(char *var, char *value, char *args)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (args[i] && args[i] != '$')
		i++;
	if (args[i])
	{
		ret = ft_strndup(args, i);
		ret = ft_strjoin_free(ret, value);
		i += ft_strlen(var);
		ret = ft_strjoin_free(ret, &args[i]);
	}
	free(args);
	return (ret);
}

char	*get_from_env(t_data *data, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i] && ft_strncmp(data->env[i], &var[1], ft_strlen(&var[1])))
		i++;
	while (data->env[i] && data->env[i][j] != '=')
		j++;
	if (data->env[i] && data->env[i][j] == '=')
	{
		j++;
		return (&data->env[i][j]);
	}
	return (NULL);
}

char	*expand_var(t_data *data, char *args)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (args[i] != '$')
		i++;
	if (args[i])
		j++;
	while (args[i + j] && (!ft_isspace(args[i + j]) && args[i + j] != '$' && args[i + j] != '"' && args[i + j] != '\''))
		j++;
	var = ft_strndup(&args[i], &args[i + j] - &args[i]);
	args = ft_replace(var, get_from_env(data, var), args);
	return (args);
}

void	expansor(char **args, t_data *data)
{
	int	i;
	int	j;
	int	d_quote;
	int	s_quote;

	i = 0;
	j = 0;
	d_quote = 0;
	s_quote = 0;
	while (args && args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '"')
			{
				set_quotes(args[i][j], &d_quote, &s_quote); // comprobar que esto funciona cuando migu haga lo del pipex
				/*if (args[i][j] == '\'' && !s_quote && !d_quote)
					s_quote = 1;
				else if (args[i][j] == '\'' && s_quote)
					s_quote = 0;
				if (args[i][j] == '"' && !d_quote && !s_quote)
					d_quote = 1;
				else if (args[i][j] == '"' && d_quote)
					d_quote = 0;*/
			}
			else if (args[i][j] == '$' && !s_quote)
				args[i] = expand_var(data, args[i]);
			if (args[i][j])
				j++;
		}
		j = 0;
		i++;
	}
}
