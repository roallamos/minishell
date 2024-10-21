/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:50:18 by migumore          #+#    #+#             */
/*   Updated: 2024/10/21 16:39:00 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_array(void **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
		array = NULL;
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

void	ft_free_lst(t_data *data)
{
	t_cmd	*next;
	int		i;

	while (data->list)
	{
		i = 0;
		next = data->list->next;
		ft_free_array((void **)data->list->args);
		while (data->list->docs && data->list->docs[i].doc)
			free(data->list->docs[i++].doc);
		free(data->list->docs);
		free(data->list);
		data->list = next;
	}
}

void	ft_free_pids(pid_t *pids)
{
	if (pids)
	{
		free(pids);
		pids = NULL;
	}
}

void	ft_free_all(t_data *data)
{
	ft_free_array((void **)data->env);
	ft_free_array((void **)data->path);
	ft_free_lst(data);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	rl_clear_history();
	ft_free_pids(data->pids);
}
