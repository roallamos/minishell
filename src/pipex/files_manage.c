/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:31 by migumore          #+#    #+#             */
/*   Updated: 2024/07/09 13:16:35 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	here_doc(t_pipex *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) == 0)
			break ;
		write(data->fd_infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(data->fd_infile);
	data->fd_infile = open("here_doc", O_RDONLY);
	if (data->fd_infile < 0)
	{
		write_error("pipex: No such file or directory: ", "here_doc");
		ft_free_cmds_n_limiter_n_pids(data);
		ft_free_path(data);
		exit(1);
	}
}

void	infile(t_pipex *data)
{
	if (data->mode == 2)
	{
		data->fd_infile = open(data->infl, O_RDONLY);
		if (data->fd_infile < 0)
		{
			write_error("pipex: No such file or directory: ", data->infl);
			ft_free_cmds_n_limiter_n_pids(data);
			ft_free_path(data);
			exit(1);
		}
	}
	else
	{
		data->fd_infile = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->fd_infile < 0)
		{
			write_error("pipex: No such file or directory: ", "here_doc");
			ft_free_cmds_n_limiter_n_pids(data);
			ft_free_path(data);
			unlink("here_doc");
			exit(1);
		}
		here_doc(data);
	}
}

void	outfile(t_pipex *data)
{
	if (data->mode == 2)
	{
		data->fd_outfile = open(data->outfl, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->fd_outfile < 0)
		{
			write_error("pipex: No such file or directory: ", data->outfl);
			ft_free_cmds_n_limiter_n_pids(data);
			ft_free_path(data);
			exit(1);
		}
	}
	else
	{
		data->fd_outfile = open(data->outfl, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (data->fd_outfile < 0)
		{
			write_error("pipex: No such file or directory: ", data->outfl);
			ft_free_cmds_n_limiter_n_pids(data);
			ft_free_path(data);
			exit(1);
		}
	}
}
