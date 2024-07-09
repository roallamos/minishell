/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:03:26 by migumore          #+#    #+#             */
/*   Updated: 2024/07/09 13:17:42 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
