/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/17 16:50:26 by migumore         ###   ########.fr       */
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
		return (do_exit(data, in_child));
	return (0);
}

static int	open_heredocs(t_data *data)
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
			if (data->list->docs[i].flag == HEREDOC)
				stop = heredoc(data, i);
			i++;
		}
		data->list = data->list->next;
	}
	data->list = tmp;
	return (stop);
}

static void	open_files(t_data *data)
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
	int	stop;

	stop = open_heredocs(data);
	if (!stop)
		open_files(data);
	if (!data->stop_exec_hd)
	{
		if (data->num_commands == 1)
		{
			if (check_builtin(data, 0) == 1)
				return ;
		}
		cmds_exec(data);
	}
	delete_heredocs(data);
}
