/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:24:43 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/11 20:07:02 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_new_var(char **env, char *new_var, int *size)
{
	env = ft_realloc(env, *size * sizeof(char *), (*size + 2) * sizeof(char *));
	env[*size] = ft_strdup(new_var);
	env[*size + 1] = NULL;
	*size += 1;
	return (env);
}

void	ft_replace_value(char **old_value, char **new_value)
{
	char	*tmp;

	tmp = *old_value;
	*old_value = ft_strdup(*new_value);
	free(tmp);
}

int	check_export(char *export, t_data *data)
{
	int	i;

	i = 0;
	data->d_quote = 0;
	data->s_quote = 0;
	while (export[i] && (export[i] != '=' || i == 0))
	{
		set_quotes(export[i], &data->d_quote, &data->s_quote);
		if ((i == 0 && !ft_isalpha(export[i]))
			|| (i != 0 && !ft_isalnum(export[i])))
		{
			printf("export: %s not a valid identifier\n", export);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	g_exit_status = 0;
	data->d_quote = 0;
	data->s_quote = 0;
	return (1);
}

void	export(t_data *data)
{
	int	size;
	int	i;
	int	j;

	i = -1;
	size = env_size(data->env);
	while (data->list->args[++i])
	{
		j = 0;
		if (ft_strcmp(data->list->args[i], "export")
			&& check_export(data->list->args[i], data)
			&& ft_strchr(data->list->args[i], '='))
		{
			while (data->env && data->env[j]
				&& ft_strncmp(data->env[j], data->list->args[i],
					ft_lgth(data->env[j], data->list->args[i])))
				j++;
			if (data->env && data->env[j])
				ft_replace_value(&data->env[j], &data->list->args[i]);
			else
				data->env = ft_new_var(data->env, data->list->args[i], &size);
		}
	}
}
