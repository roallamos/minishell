/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:50:18 by migumore          #+#    #+#             */
/*   Updated: 2024/10/15 08:07:46 by migumore         ###   ########.fr       */
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
