/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:50:18 by migumore          #+#    #+#             */
/*   Updated: 2024/09/25 19:24:31 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_array(char **array)
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

void	ft_free_lst(t_data *data)
{
	t_cmd	*next;
	int		i;

	while (data->list)
	{
		i = 0;
		next = data->list->next;
		ft_free_array(data->list->args);
		while (data->list->docs && data->list->docs[i].doc)
			free(data->list->docs[i++].doc);
		free(data->list->docs);
		free(data->list);
		data->list = next;
	}
}
