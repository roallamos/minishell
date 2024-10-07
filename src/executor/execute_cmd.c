/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:21:41 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/07 13:56:43 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_cmd_and_execute(t_data *data)
{

	data->path_in_env = ft_find_path(data->env);
	data->path = ft_split(data->path_in_env, ':');
	if (check_builtin(data, 1) != 0)
		exit(1);
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
	ft_free_lst(data);
	ft_free_array(data->path);
	exit(1);
}
