/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:21:41 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/19 09:45:25 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_cmd_and_execute(t_data *data)
{
	if (check_builtin(data) == 0)
	{
		rl_clear_history();
		data->list->cmd = ft_get_cmd(data->path, data->list->args[0]);
		if (!data->list->cmd)
		{
			write_error("minishell: command not found: ", data->list->args[0]);
			ft_free_lst(data);
			exit(127);
		}
		execve(data->list->cmd, data->list->args, data->env);
		perror("execve");
		exit(1);
	}
}
