/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:50:18 by migumore          #+#    #+#             */
/*   Updated: 2024/06/21 19:40:05 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_args(t_data *data)
{
	int	i;

	if (data->args)
	{
		i = 0;
		while (data->args[i])
		{
			free(data->args[i]);
			i++;
		}
		free(data->args);
	}
	if (data->cmd)
		free(data->cmd);
}

void	ft_free_path(t_data *data)
{
	int	i;

	i = 0;
	if (data->path)
	{
		while (data->path[i])
			free(data->path[i++]);
		free(data->path);
	}
}
void	ft_free_env(t_data *data)
{
	int	i;

	i = 0;
	while(data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
}

