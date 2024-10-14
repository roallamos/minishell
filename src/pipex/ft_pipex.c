/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:38:30 by migumore          #+#    #+#             */
/*   Updated: 2024/10/14 19:45:57 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	do_pipe(t_data *data)
{
	int	i;

	data->pipefd = malloc((data->num_commands - 1) * sizeof(int *));
	if (data->pipefd == NULL)
		return (1);
	i = 0;
	while (i < data->num_commands - 1)
	{
		data->pipefd[i] = malloc(2 * sizeof(int));
		if (data->pipefd[i] == NULL || pipe(data->pipefd[i]) == -1)
		{
			perror("pipe");
			if (data->pids)
				free(data->pids);
			ft_free_array(data->pipefd);
			return (1);
		}
		i++;
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
		close_pipes(data, data->num_commands);
		return (1);
	}
	return (0);
}

int	allocate_pids(t_data *data)
{
	data->pids = malloc(sizeof(pid_t) * data->num_commands);
	if (!data->pids)
	{
		perror("malloc");
		return (1);
	}
	return (0);
}

static int	pipex(t_data *data, int i, t_cmd *list)
{
	pid_t		pid;

	if (do_fork(&pid, data))
		return (1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		pipes_redirs(data, i);
		files_redirs(data);
		close_files(list);
		get_cmd_and_execute(data);
	}
	else
		data->pids[i] = pid;
	return (0);
}

void	exec_pipex(t_data *data)
{
	int			i;
	t_cmd		*tmp;

	if (allocate_pids(data))
		return ;
	i = 0;
	tmp = data->list;
	if (do_pipe(data))
		return ;
	while (i < data->num_commands)
	{
		if (pipex(data, i, tmp))
			break ;
		signal(SIGINT, SIG_IGN);
		data->list = data->list->next;
		i++;
	}
	data->list = tmp;
	close_pipes(data, 0);
	close_files(data->list);
	wait_pids(data, 0);
	if (data->pids)
		free(data->pids);
}
