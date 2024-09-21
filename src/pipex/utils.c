/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:59:37 by migumore          #+#    #+#             */
/*   Updated: 2024/09/21 15:09:08 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	delete_here_docs(t_data *data)
{
	int	i;
	int	j;
	t_cmd	*tmp;

	i = 0;
	tmp = data->list;
	while (i < data->num_commands)
	{
		j = 0;
		while (data->list->docs && data->list->docs[j].doc)
		{
			if (data->list->docs[j].flag == 1)
				unlink(data->list->docs[j].doc);
			j++;
		}
		data->list = data->list->next;
		i++;
	}
	data->list = tmp;
}

void	wait_pids(t_data *data, int i)
{
	while (i < data->num_commands)
	{
		if (i == data->num_commands - 1)
			waitpid(data->pids[i], &data->status, 0);
		else
			waitpid(data->pids[i], NULL, 0);
		i++;
	}
}
