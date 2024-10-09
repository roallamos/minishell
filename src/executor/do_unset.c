/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:02:04 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/09 22:56:06 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_delete_var(char **env, int pos)
{
	char	**new_env;
	int		size;
	int		i;

	size = env_size(env);
	new_env = ft_calloc(size, sizeof(char *));
	i = 0;
	while (i != pos)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	while (env[i + 1])
	{
		new_env[i] = ft_strdup(env[i + 1]);
		i++;
	}
	ft_free_array(env);
	return (new_env);
}

static void	unset_oldpwd(char **oldpwd, char *arg)
{
	if (!ft_strcmp(arg, "OLDPWD"))
	{
		free(*oldpwd);
		*oldpwd = NULL;
	}
}

void	unset(t_data *data)
{
	int	i;
	int	j;
	int	n;

	if (!data->env)
		return ;
	i = 0;
	while (data->list->args[i])
	{
		j = 0;
		if (ft_strcmp(data->list->args[i], "unset"))
		{
			unset_oldpwd(&data->oldpwd, data->list->args[i]);
			n = ft_lgth(data->env[j], data->list->args[i]);
			while (data->env[j]
				&& ft_strncmp(data->env[j], data->list->args[i], n))
			{
				j++;
				n = ft_lgth(data->env[j], data->list->args[i]);
			}
			if (data->env[j])
				data->env = ft_delete_var(data->env, j);
		}
		i++;
	}
}
