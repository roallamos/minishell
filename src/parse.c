/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/07/23 15:51:54 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_builtin(t_data *data, int pos)
{
	if (!ft_strcmp(data->list->args[pos], "echo"))
		return (export(data, pos), 1); //Hacer built-in
	else if (!ft_strcmp(data->list->args[pos], "cd"))
		return (do_cd(data, pos), 1);
	else if (!ft_strcmp(data->list->args[pos], "pwd"))
		return (printf("%s\n", getcwd(NULL, 0)), 1);
	else if (!ft_strcmp(data->list->args[pos], "export"))
		return (export(data, pos), 1);
	else if (!ft_strcmp(data->list->args[pos], "unset"))
		return (export(data, pos), 1); //Hacer built-in
	else if (!ft_strcmp(data->list->args[pos], "env"))
		return (print_env(data), 1);
	else if (!ft_strcmp(data->list->args[pos], "exit"))
		do_exit(data);
	return (0);
}

void	parse(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_commands == 1)
	{
		if (check_builtin(data, i))
			return ;
		else
		{	
			data->pid = fork();
			if (data->pid == 0)
				get_cmd_and_execute(data);
			else
				waitpid(data->pid, &data->status, 0);
		}
	}
	else
		exec_pipex(data);
}
