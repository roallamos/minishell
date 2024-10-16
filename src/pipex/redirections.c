/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:10:33 by migumore          #+#    #+#             */
/*   Updated: 2024/10/16 15:28:45 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipes_redirs(t_data *data, int i, t_cmd *list)
{
	if (i > 0)
	{
		if (dup2(data->pipefd[i - 1][0], STDIN) == -1)
		{
			perror("dup2 failed");
			close_files(list);
			exit(1);
		}
	}
	if (i < data->num_commands - 1)
	{
		if (dup2(data->pipefd[i][1], STDOUT) == -1)
		{
			perror("dup2 failed");
			close_files(list);
			exit(1);
		}
	}
	close_pipes(data, 0);
}

static void	duplication(t_data *data, int i, int std, t_cmd *list)
{
	if (data->list->docs[i].fd < 0)
	{
		close_files(list);
		exit(1);
	}
	if (dup2(data->list->docs[i].fd, std) == -1)
	{
		perror("dup2 failed");
		close_files(list);
		exit(1);
	}
	close(data->list->docs[i].fd);
	data->list->docs[i].fd = -1;
}

void	files_redirs(t_data *data, t_cmd *list)
{
	int	i;

	i = 0;
	while (data->list && data->list->docs && data->list->docs[i].doc)
	{
		if (data->list->docs[i].flag == INFILE
			|| data->list->docs[i].flag == HERE_DOC)
			duplication(data, i, STDIN, list);
		else if (data->list->docs[i].flag == OUTFILE
			|| data->list->docs[i].flag == APPEND)
			duplication(data, i, STDOUT, list);
		i++;
	}
}

void	close_pipes(t_data *data, int i)
{
	while (i < data->num_commands - 1)
	{
		close(data->pipefd[i][0]);
		close(data->pipefd[i][1]);
		free(data->pipefd[i]);
		i++;
	}
	free(data->pipefd);
}
