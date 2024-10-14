/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:38:30 by migumore          #+#    #+#             */
/*   Updated: 2024/10/14 13:11:27 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	do_pipe(t_data *data, int i)
{
	if (i < data->num_commands - 1)
	{
		if (pipe(data->pipefd) == -1)
		{
			if (data->pids)
				free(data->pids);
			perror("pipe");
			return (1);
		}
	}
	else
	{
		data->pipefd[0] = -1;
		data->pipefd[1] = -1;
	}
	return (0);
}

static int	do_fork(pid_t *pid, t_data *data)
{
	*pid = fork();
	if (*pid == -1)
	{
		if (data->pids)
			free(data->pids);
		perror("fork");
		return (1);
	}
	return (0);
}

static int	allocate_pids(t_data *data)
{
	data->pids = malloc(sizeof(pid_t) * data->num_commands);
	if (!data->pids)
	{
		perror("malloc");
		return (1);
	}
	return (0);
}

static int	pipex(t_data *data, int *prev_pipefd, int i)
{
	pid_t		pid;

	if (do_pipe(data, i))
		return (1);
	if (do_fork(&pid, data))
		return (1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		pipes_redirs(data, prev_pipefd, i);
		files_redirs(data);
		close_files(data);
		get_cmd_and_execute(data);
	}
	else
	{
		data->pids[i] = pid;
		close_pipes(data, prev_pipefd, i, 0);
		close_files(data);
	}
	return (0);
}

void	exec_pipex(t_data *data)
{
	int			i;
	t_cmd		*tmp;
	static int	prev_pipefd;

	if (allocate_pids(data))
		return ;
	i = 0;
	tmp = data->list;
	prev_pipefd = -1;
	while (i < data->num_commands)
	{
		if (pipex(data, &prev_pipefd, i))
			break ;
		signal(SIGINT, SIG_IGN);
		data->list = data->list->next;
		i++;
	}
	wait_pids(data, 0);
	prev_pipefd = -1;
	data->list = tmp;
	if (data->pids)
		free(data->pids);
}
