/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:21:41 by rodralva          #+#    #+#             */
/*   Updated: 2024/07/09 14:48:39 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_cmd_and_execute(t_data *data)
{
	rl_clear_history();
	//data->args = ft_split_input(data->commands[0], data);
	data->list->cmd = ft_get_cmd(data->path, data->list->args[0]);
	if (!data->list->cmd)
	{
		write_error("minishell: command not found: ", data->list->args[0]);
		ft_free_lst(data);
		//ft_free_args(data);
		//ft_free_path(data);
		//ft_free_env(data);
		exit(127);
	}
	execve(data->list->cmd, data->list->args, data->env);
	perror("execve");
	exit(1);
}
