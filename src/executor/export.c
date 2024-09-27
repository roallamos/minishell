/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:24:43 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/27 12:53:16 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_lgth(const char *s1, const char* s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	while (s2[j] && s2[j] != '=')
		j++;
	if (i > j)
		return (i);
	else
		return (j);
}

char	**ft_new_var(char **env, char *new_var, int *size)
{
	printf("size %d\n", env_size(env));
	env = ft_realloc(env, *size * sizeof(char *), (*size + 2) * sizeof(char *));
	env[*size] = ft_strdup(new_var);
	env[*size + 1] = NULL;
	printf("size %d\n", env_size(env));
	*size += 1;
	return (env);
}

void	ft_replace_value(char **old_value, char **new_value)
{
	int i;
	char *tmp;

	i = 0;
	tmp = *old_value;
	*old_value = ft_strdup(*new_value);
	free(tmp);
}

void	export(t_data *data)
{
	int	size;
	int	i;
	int	j;
	int	n;

	i = 0;
	size = env_size(data->env);
	printf("size %d\n", size);
	while (data->list->args[i])
	{
		if (ft_strcmp(data->list->args[i], "export"))
		{
			n = ft_lgth(data->env[j], data->list->args[i]);
			while (data->env[j] && ft_strncmp(data->env[j], data->list->args[i], n))
				j++;
			if (data->env[j])
				ft_replace_value(&data->env[j], &data->list->args[i]);
			else
				data->env = ft_new_var(data->env, data->list->args[i], &size);
		}
		j = 0;
		i++;
	}
}
