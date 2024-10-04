/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/04 15:46:19 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_builtin(t_data *data)
{
	if (!data->list->args || !data->list->args[0])
		return (2);
	else if (!ft_strcmp(data->list->args[0], "echo"))
		return (do_echo(data), 1);
	else if (!ft_strcmp(data->list->args[0], "cd"))
		return (do_cd(data, 0), 1);
	else if (!ft_strcmp(data->list->args[0], "pwd"))
		return (printf("%s\n", ft_find_pwd(data->env)), 1);
	else if (!ft_strcmp(data->list->args[0], "export"))
		return (export(data), 1);
	else if (!ft_strcmp(data->list->args[0], "unset"))
		return (unset(data), 1);
	else if (!ft_strcmp(data->list->args[0], "env"))
		return (print_env(data), 1);
	else if (!ft_strcmp(data->list->args[0], "exit"))
		do_exit(data);
	return (0);
}

void	open_files(t_data *data)
{
	int		i;
	t_cmd	*tmp;

	tmp = data->list;
	while (data->list)
	{
		i = 0;
		while (data->list->docs && data->list->docs[i].doc)
		{
			if (data->list->docs[i].flag == INFILE)
				infile(data, i);
			if (data->list->docs[i].flag == HERE_DOC)
				heredoc(data, i);
			if (data->list->docs[i].flag == OUTFILE)
				outfile(data, i);
			if (data->list->docs[i].flag == APPEND)
				append(data, i);
			i++;
		}
		data->list = data->list->next;
	}
	data->list = tmp;
}

void	execute(t_data *data)
{
	int	original_stdin;
	int	original_stdout;

	dup_stds(&original_stdin, &original_stdout);
	open_files(data);
	if (data->num_commands == 1)
	{
		if (check_builtin(data) == 1)
			return ;
		else
		{
			data->pid = fork();
			if (data->pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				one_cmd_redirs(data);
				get_cmd_and_execute(data);
			}
			waitpid(data->pid, &data->status, 0);
			if (WIFEXITED(data->status))
				g_exit_status = WEXITSTATUS(data->status);
			else if (WIFSIGNALED(data->status))
				g_exit_status = WTERMSIG(data->status) + 128;
		}
	}
	else
		exec_pipex(data);
	delete_here_docs(data);
	reset_stds(original_stdin, original_stdout);
}
