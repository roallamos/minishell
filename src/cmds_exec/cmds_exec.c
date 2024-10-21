/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:38:30 by migumore          #+#    #+#             */
/*   Updated: 2024/10/21 16:39:36 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	allocate_pids(t_data *data)
{
	data->pids = malloc(sizeof(pid_t) * data->num_commands);
	if (!data->pids)
	{
		perror("malloc pids");
		return (1);
	}
	return (0);
}

static int	do_pipe(t_data *data)
{
	int	i;

	data->pipefd = ft_calloc((data->num_commands), sizeof(int *));
	if (data->pipefd == NULL)
	{
		perror("malloc pipefd");
		return (1);
	}
	i = 0;
	while (i < data->num_commands - 1)
	{
		data->pipefd[i] = ft_calloc(2, sizeof(int));
		if (data->pipefd[i] == NULL || pipe(data->pipefd[i]) == -1)
		{
			perror("malloc pipefd[i] or pipe");
			if (data->pids)
				free(data->pids);
			ft_free_array((void **)data->pipefd);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	do_fork(t_data *data, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		if (data->pids)
			free(data->pids);
		perror("fork");
		close_pipes(data, data->num_commands);
		return (1);
	}
	return (0);
}

static int	child_process(t_data *data, int i, t_cmd *list, int is_piped)
{
	if (do_fork(data, i))
		return (1);
	if (data->pids[i] == 0)
	{
		rl_clear_history();
		signal(SIGQUIT, SIG_DFL);
		pipes_redirs(data, i, list);
		if (!data->list->stop_exec)
			files_redirs(data, list);
		close_files(list);
		if (data->file_fd > -1)
			close(data->file_fd);
		if (data->list->stop_exec)
		{
			ft_free_all(data);
			exit(1);
		}
		get_cmd_and_execute(data, is_piped);
	}
	return (0);
}

void	cmds_exec(t_data *data, int is_piped)
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
		if (child_process(data, i, tmp, is_piped))
			break ;
		signal(SIGINT, SIG_IGN);
		data->list = data->list->next;
		i++;
	}
	data->list = tmp;
	close_pipes(data, 0);
	close_files(data->list);
	wait_pids(data, 0);
	ft_free_pids(data->pids);
}
