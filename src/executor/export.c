/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:24:43 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/24 19:25:10 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export(t_data *data, int pos)
{
	int	size;

	size = env_size(data->env);
	if (data->commands[pos + 1])
	{
		data->env = ft_realloc(data->env, size * sizeof(char *),
				(size + 1) * sizeof(char *));
		data->env[size] = ft_strndup(data->args[pos + 1],
				ft_strlen(data->args[pos + 1]));
		data->env[size + 1] = NULL;
	}
}
