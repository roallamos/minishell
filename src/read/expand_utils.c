/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:05:16 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/10 18:15:09 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_replace(char *var, char *value, char *args)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while ((args[i] && args[i] != '$') || (args[i] && args[i] == '$'
			&& (args[i + 1] == '"' || args[i + 1] == '\'')))
		i++;
	if (args[i])
	{
		ret = ft_strndup(args, i);
		ret = ft_strjoin_free(ret, value);
		i += ft_strlen(var);
		ret = ft_strjoin_free(ret, &args[i]);
	}
	free(args);
	free(var);
	free(value);
	return (ret);
}

char	*get_from_env(t_data *data, char *var)
{
	int	i;
	int	j;
	int	stat;

	i = 0;
	j = 0;
	stat = 0;
	if (!ft_strcmp(var, "$?"))
	{
		stat = g_exit_status | stat;
		return (ft_itoa(stat));
	}
	while (data->env && data->env[i] && ft_strncmp(data->env[i], &var[1],
			ft_strlen(&var[1])))
		i++;
	while (data->env && data->env[i] && data->env[i][j] != '=')
		j++;
	if (data->env && data->env[i] && data->env[i][j] == '=')
	{
		j++;
		return (ft_strdup(&data->env[i][j]));
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
	var = NULL;
	while ((args[i] && args[i] != '$') || (args[i] && args[i] == '$'
			&& (args[i + 1] == '"' || args[i + 1] == '\'')))
		i++;
	if (args[i])
		j++;
	if (args[i + j] && args[i + j] == '?')
		var = ft_strdup("$?");
	while (!var && args[i + j] && (!ft_isspace(args[i + j])
			&& args[i + j] != '$'
			&& args[i + j] != '"' && args[i + j] != '\''))
		j++;
	if (!var)
		var = ft_strndup(&args[i], &args[i + j] - &args[i]);
	args = ft_replace(var, get_from_env(data, var), args);
	return (args);
}

void	remove_dollar(char **args, int i, int *j, int *flag)
{
	ft_memmove(&args[i][*j], &args[i][*j + 1], ft_strlen(&args[i][*j]));
	*flag = 0;
	j--;
}
