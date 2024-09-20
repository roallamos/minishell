/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/20 10:50:27 by migumore         ###   ########.fr       */
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

int	do_redirs(t_data *data)
{
	int	i;

	i = 0;
	while (data->list->docs && data->list->docs[i].doc)
	{
		if (data->list->docs[i].flag == INFILE
			|| data->list->docs[i].flag == HERE_DOC)
		{
			if (data->list->docs[i].fd < 0)
				return (0);
			dup2(data->list->docs[i].fd, STDIN_FILENO);
			close(data->list->docs[i].fd);
		}
		else
		{
			if (data->list->docs[i].fd < 0)
				return (0);
			dup2(data->list->docs[i].fd, STDOUT_FILENO);
			close(data->list->docs[i].fd);
		}
		i++;
	}
	return (1);
}

void	parse(t_data *data)
{
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	check_redirs(data);
	if (data->num_commands == 1)
	{
		if (do_redirs(data) == 1)
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
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}
