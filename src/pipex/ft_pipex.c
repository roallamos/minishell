/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:38:30 by migumore          #+#    #+#             */
/*   Updated: 2024/09/18 12:41:16 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	do_pipe(t_data *data, int i)
{
	if (i < data->num_commands - 1)
	{
		if (pipe(data->pipefd) == -1)
			perror("pipe");
	}
}

static void	do_fork(pid_t *pid)//, t_data *data)
{
	*pid = fork();
	if (*pid == -1)
		perror("fork");
}

static void	allocate_pids(t_data *data)
{
	data->pids = malloc(sizeof(pid_t) * data->num_commands);
	if (!data->pids)
		perror("malloc");
}

static void	pipex(t_data *data, int i, int j)
{
	pid_t		pid;
	static int	prev_pipefd[2] = {-1, -1};

	do_pipe(data, i);
	do_fork(&pid);
	if (pid == 0)
	{
		j = 0;
		while (data->list->docs && data->list->docs[j].doc)
		{
			if (data->list->docs[j].flag == 0 || data->list->docs[j].flag == 1)
				dup_infile_n_close(data, j);
			if (data->list->docs[j].flag == 2 || data->list->docs[j].flag == 3)
				dup_outfile_n_close(data, j);
			j++;
		}
		if (!data->list->docs)
			dup_cmds_n_close(data, &prev_pipefd);
		get_cmd_and_execute(data);
	}
	else
	{
		data->pids[i] = pid;
		close_pipes(data, &prev_pipefd, i);
	}
}

void	exec_pipex(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	allocate_pids(data);
	i = 0;
	j = 0;
	tmp = data->list;
	while (i < data->num_commands)
	{
		pipex(data, i, j);
		data->list = data->list->next;
		i++;
	}
	wait_pids(data, 0);
	data->list = tmp;
	delete_here_docs(data);
	data->list = tmp;
}
