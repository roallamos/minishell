/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:10:33 by migumore          #+#    #+#             */
/*   Updated: 2024/10/14 13:12:02 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipes_redirs(t_data *data, int *prev_pipefd, int i)
{
	if (i > 0)
	{
		if (dup2(*prev_pipefd, STDIN) == -1)
		{
			perror("dup2 failed");
			exit(1);
		}
	}
	if (i < data->num_commands - 1)
	{
		if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			exit(1);
		}
	}
	close_pipes(data, prev_pipefd, i, 1);
}

static void	duplication(t_data *data, int i, int std)
{
	if (data->list->docs[i].fd < 0)
		exit(1);
	if (dup2(data->list->docs[i].fd, std) == -1)
	{
		perror("dup2 failed");
		exit(1);
	}
	close(data->list->docs[i].fd);
}

void	files_redirs(t_data *data)
{
	int	i;

	i = 0;
	while (data->list->docs && data->list->docs[i].doc)
	{
		if (data->list->docs[i].flag == INFILE
			|| data->list->docs[i].flag == HERE_DOC)
			duplication(data, i, STDIN);
		else if (data->list->docs[i].flag == OUTFILE
			|| data->list->docs[i].flag == APPEND)
			duplication(data, i, STDOUT);
		i++;
	}
}

void	close_pipes(t_data *data, int *prev_pipefd, int i, int in_child)
{
	if (*prev_pipefd != -1)
	{
		close(*prev_pipefd);
		*prev_pipefd = -1;
	}
	if (i != data->num_commands - 1 && !in_child)
		*prev_pipefd = dup(data->pipefd[0]);
	if (data->pipefd[0] != -1)
	{
		close(data->pipefd[0]);
		data->pipefd[0] = -1;
	}
	if (data->pipefd[1] != -1)
	{
		close(data->pipefd[1]);
		data->pipefd[1] = -1;
	}
}
