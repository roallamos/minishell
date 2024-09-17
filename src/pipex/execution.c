/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:10:33 by migumore          #+#    #+#             */
/*   Updated: 2024/09/17 15:27:32 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	dup_infile_n_close(t_data *data)
// {
// 	if (data->list->fd_infile)
// 	{
// 		close(data->pipefd[0]);
// 		dup2(data->list->fd_infile, STDIN_FILENO);
// 		dup2(data->pipefd[1], STDOUT_FILENO);
// 		close(data->list->fd_infile);
// 	}
// 	else if (data->list->fd_heredoc)
// 	{
// 		close(data->pipefd[0]);
// 		dup2(data->list->fd_heredoc, STDIN_FILENO);
// 		dup2(data->pipefd[1], STDOUT_FILENO);
// 		close(data->list->fd_heredoc);
// 	}
// }

// void	dup_outfile_n_close(t_data *data)
// {
// 	if (data->list->fd_outfile)
// 	{
// 		close(data->pipefd[1]);
// 		dup2(data->list->fd_outfile, STDOUT_FILENO);
// 		dup2(data->pipefd[0], STDIN_FILENO);
// 		close(data->list->fd_outfile);
// 	}
// 	else if (data->list->fd_append)
// 	{
// 		close(data->pipefd[1]);
// 		dup2(data->list->fd_append, STDOUT_FILENO);
// 		dup2(data->pipefd[0], STDIN_FILENO);
// 		close(data->list->fd_append);
// 	}
// }

// void	dup_cmds_n_close(t_data *data, int (*prev_pipefd)[2])
// {
// 	if ((*prev_pipefd)[0] != -1 && (*prev_pipefd)[1] != -1)
// 	{
// 		dup2((*prev_pipefd)[0], STDIN_FILENO);
// 		close((*prev_pipefd)[0]);
// 		close((*prev_pipefd)[1]);
// 	}
// 	dup2(data->pipefd[1], STDOUT_FILENO);
// 	close(data->pipefd[0]);
// 	close(data->pipefd[1]);
// }

// void	close_pipes(t_data *data, int (*prev_pipe)[2], int i)
// {
// 	if (i != 0)
// 	{
// 		close((*prev_pipe)[0]);
// 		close((*prev_pipe)[1]);
// 	}
// 	if (i != data->num_commands - 1)
// 	{
// 		(*prev_pipe)[0] = data->pipefd[0];
// 		(*prev_pipe)[1] = data->pipefd[1];
// 	}
// }
