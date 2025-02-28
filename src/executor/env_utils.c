/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:17:20 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/17 17:50:32 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*update_shlvl(char *env)
{
	int		lvl;
	char	*s_lvl;
	char	*shlvl;

	lvl = ft_atoi(env + 6);
	lvl++;
	s_lvl = ft_itoa(lvl);
	shlvl = ft_strjoin("SHLVL=", s_lvl);
	free(s_lvl);
	return (shlvl);
}

int	env_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

static void	no_env(t_data *data)
{
	data->env = ft_calloc(sizeof(char *), 2 + 1);
	if (!data->env)
		return ;
	data->env[0] = ft_strjoin("PWD=", data->pwd);
	data->env[1] = ft_strdup("SHLVL=1");
}

void	dup_env(t_data *data, char **env)
{
	int	i;
	int	size;

	i = 0;
	size = env_size(env);
	if (size)
	{
		data->env = ft_calloc(sizeof(char *), size + 1);
		if (!data->env)
			return ;
		while (i < size)
		{
			if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
				data->env[i] = update_shlvl(env[i]);
			else
				data->env[i] = ft_strdup(env[i]);
			i++;
		}
	}
	else
		no_env(data);
}

int	ft_lgth(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] != '=')
		i++;
	while (s2[j] && s2[j] != '=')
		j++;
	if (i > j)
		return (i);
	else
		return (j);
}
