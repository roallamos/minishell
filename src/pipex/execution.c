/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:10:33 by migumore          #+#    #+#             */
/*   Updated: 2024/07/09 19:50:29 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dup_infile_n_close(t_data *data)
{
	int	i;

	i = 0;
	while (data->list->infile[i] || data->list->heredoc[i])
	{
		infile(data, i);
		i++;
	}
	close(data->pipefd[0]);
	dup2(data->fd_infile, STDIN_FILENO);
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->fd_infile);
}

void	dup_outfile_n_close(t_data *data)
{
	int	i;

	i = 0;
	while (data->list->outfile[i] || data->list->append[i])
	{
		outfile(data, i);
		i++;
	}
	dup2(data->fd_outfile, STDOUT_FILENO);
	dup2(data->pipefd[0], STDIN_FILENO);
	close(data->pipefd[1]);
	close(data->fd_outfile);
}

void	dup_cmds_n_close(t_data *data, int (*prev_pipefd)[2])
{
	if ((*prev_pipefd)[0] != -1 && (*prev_pipefd)[1] != -1)
	{
		dup2((*prev_pipefd)[0], STDIN_FILENO);
		close((*prev_pipefd)[0]);
		close((*prev_pipefd)[1]);
	}
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}

void	close_pipes(t_data *data, int (*prev_pipe)[2], int i)
{
	if (i != 0)
	{
		close((*prev_pipe)[0]);
		close((*prev_pipe)[1]);
	}
	if (i != data->num_commands - 1)
	{
		(*prev_pipe)[0] = data->pipefd[0];
		(*prev_pipe)[1] = data->pipefd[1];
	}
}
