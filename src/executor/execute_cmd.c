/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:21:41 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/22 15:53:43 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_cmd_and_execute(t_data *data)
{
	rl_clear_history();
	data->cmd = ft_get_cmd(data->path, data->args[0]);
	if (!data->cmd)
	{
		write_error("minishell: command not found: ", data->args[0]);
		ft_free_args(data);
		ft_free_path(data);
		ft_free_env(data);
		exit(127);
	}
	ft_free_env(data);
	execve(data->cmd, data->args, data->env);
	perror("execve");
	exit(1);
}