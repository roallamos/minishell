/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/15 17:21:49 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_builtin(t_data *data, int in_child)
{
	if (!data->list->args || !data->list->args[0])
		return (2);
	else if (in_child == 1 && !ft_strcmp(data->list->args[0], "echo"))
		return (do_echo(data), 1);
	else if (!ft_strcmp(data->list->args[0], "cd"))
		return (do_cd(data, 0), 1);
	else if (in_child == 1 && !ft_strcmp(data->list->args[0], "pwd"))
	{
		if (!data->pwd)
			data->pwd = getcwd(NULL, 0);
		return (printf("%s\n", data->pwd), 1);
	}
	else if (!ft_strcmp(data->list->args[0], "export"))
		return (export(data), 1);
	else if (!ft_strcmp(data->list->args[0], "unset"))
	{
		g_exit_status = 0;
		return (unset(data), 1);
	}
	else if (in_child == 1 && !ft_strcmp(data->list->args[0], "env"))
		return (print_env(data), 1);
	else if (!ft_strcmp(data->list->args[0], "exit"))
		do_exit(data);
	return (0);
}

void	open_files(t_data *data)
{
	int		i;
	t_cmd	*tmp;
	int		stop;

	tmp = data->list;
	while (data->list)
	{
		stop = 0;
		i = 0;
		while (data->list->docs && data->list->docs[i].doc && stop == 0)
		{
			if (data->list->docs[i].flag == INFILE)
				stop = infile(data, i);
			if (data->list->docs[i].flag == HERE_DOC)
				stop = heredoc(data, i);
			if (data->list->docs[i].flag == OUTFILE)
				stop = outfile(data, i);
			if (data->list->docs[i].flag == APPEND)
				stop = append(data, i);
			i++;
		}
		data->list = data->list->next;
	}
	data->list = tmp;
}

void	execute(t_data *data)
{
	open_files(data);
	if (!data->stop_exec)
	{
		if (data->num_commands == 1)
		{
			if (check_builtin(data, 0) == 1)
				return ;
		}
		exec_pipex(data);
	}
	close_files(data->list);
	delete_here_docs(data);
}
