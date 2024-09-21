/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/21 14:59:14 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_builtin(t_data *data)
{
	if (!ft_strcmp(data->list->args[0], "echo"))
		return (export(data), 1); // falta built in
	else if (!ft_strcmp(data->list->args[0], "cd"))
		return (do_cd(data, 0), 1);
	else if (!ft_strcmp(data->list->args[0], "pwd"))
		return (printf("%s\n", getcwd(NULL, 0)), 1);
	else if (!ft_strcmp(data->list->args[0], "export"))
		return (export(data), 1);
	else if (!ft_strcmp(data->list->args[0], "unset"))
		return (export(data), 1); //Hacer built-in
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

void	reset_stds(int in, int out)
{
	dup2(in, STDIN_FILENO);
	close(in);
	dup2(out, STDOUT_FILENO);
	close(out);
}

void	execute(t_data *data)
{
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	open_files(data);
	if (data->num_commands == 1)
	{
		if (one_cmd_redirs(data) == 1)
		{
			if (check_builtin(data))
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
		delete_here_docs(data);
	}
	else
		exec_pipex(data);
	reset_stds(original_stdin, original_stdout);
}
