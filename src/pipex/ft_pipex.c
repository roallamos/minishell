/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:38:30 by migumore          #+#    #+#             */
/*   Updated: 2024/09/17 18:27:29 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	do_pipe(t_data *data, int i)
{
	if (i < data->num_commands - 1)
	{
		if (pipe(data->pipefd) == -1)
		{
			// ft_free_cmds_n_limiter_n_pids(data);
			// ft_free_path(data);
			perror("pipe");
			// exit(-1);
		}
		printf("pipes\n");
	}
}

static void	do_fork(pid_t *pid)//, t_data *data)
{
	*pid = fork();
	printf("fork1\n");
	if (*pid == -1)
	{
		// ft_free_cmds_n_limiter_n_pids(data);
		// ft_free_path(data);
		perror("fork");
		// exit(-1);
	}
}

static void	allocate_pids(t_data *data)
{
	data->pids = malloc(sizeof(pid_t) * data->num_commands);
	printf("pids\n");
	if (!data->pids)
	{
	// 	ft_free_cmds_n_limiter_n_pids(data);
	// 	ft_free_path(data);
		perror("malloc");
	// 	exit(1);
	}
}

static void	pipex(t_data *data, int i)
{
	pid_t		pid;
	static int	prev_pipefd[2] = {-1, -1};

	do_pipe(data, i);
	do_fork(&pid);//, data);
	if (pid == 0)
	{
		if (data->list->docs[i].flag == 0 || data->list->docs[i].flag == 1)
		{
			printf("con infile");
			dup_infile_n_close(data, i);
		}
		else if (data->list->docs[i].flag == 2 || data->list->docs[i].flag == 3)
		{
			printf("con outfile");
			dup_outfile_n_close(data, i);
		}
		else
		{
			printf("solo cmds");
			dup_cmds_n_close(data, &prev_pipefd);
		}
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

	//parse_argvb(argc, &data);
	allocate_pids(data);
	i = 0;
	while (i < data->num_commands)
	{
		printf("pipex\n");
		pipex(data, i);
		data->list = data->list->next;
		i++;
	}
	wait_pids(data, 0);
	//unlink("here_doc");
}
