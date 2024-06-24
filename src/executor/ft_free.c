/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:50:18 by migumore          #+#    #+#             */
/*   Updated: 2024/06/24 18:44:04 by migumore         ###   ########.fr       */
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
			data->args[i] = NULL;
			i++;
		}
		free(data->args);
		data->args = NULL;
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
	if (data->env)
	{
		while (data->env[i])
		{
			free(data->env[i]);
			i++;
		}
		free(data->env);
	}
}

void	ft_free_cmds_n_limiter_n_pids(t_data *data)
{
	int	i;

	i = 0;
	if (data->commands)
	{
		while (data->commands[i])
			free(data->commands[i++]);
		free(data->commands);
	}
	if (data->limiter)
		free(data->limiter);
	// if (data->pids)
	// 	free(data->pids);
}

