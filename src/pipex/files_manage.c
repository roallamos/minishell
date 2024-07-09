/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:31 by migumore          #+#    #+#             */
/*   Updated: 2024/07/09 19:55:35 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	here_doc(t_data *data, int i)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, data->list->append[i],
				ft_strlen(data->list->append[i])) == 0)
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
		// ft_free_cmds_n_limiter_n_pids(data);
		// ft_free_path(data);
		exit(1);
	}
}

void	infile(t_data *data, int i)
{
	if (data->list->infile)
	{
		data->fd_infile = open(data->list->infile[i], O_RDONLY);
		if (data->fd_infile < 0)
		{
			write_error("minishell: No such file or directory: ", data->list->infile[i]);
			// ft_free_cmds_n_limiter_n_pids(data);
			// ft_free_path(data);
			exit(1);
		}
	}
	else if (data->list->heredoc[i])
	{
		data->fd_infile = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->fd_infile < 0)
		{
			write_error("minishell: No such file or directory: ", "here_doc");
			// ft_free_cmds_n_limiter_n_pids(data);
			// ft_free_path(data);
			unlink("here_doc");
			exit(1);
		}
		here_doc(data, i);
	}
}

void	outfile(t_data *data, int i)
{
	if (data->list->outfile)
	{
		data->fd_outfile = open(data->list->outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->fd_outfile < 0)
		{
			write_error("minishell: No such file or directory: ", data->list->outfile[i]);
			// ft_free_cmds_n_limiter_n_pids(data);
			// ft_free_path(data);
			exit(1);
		}
	}
	else if (data->list->append[i])
	{
		data->fd_outfile = open(data->list->outfile[i], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (data->fd_outfile < 0)
		{
			write_error("minishell: No such file or directory: ", data->list->outfile[i]);
			// ft_free_cmds_n_limiter_n_pids(data);
			// ft_free_path(data);
			exit(1);
		}
	}
}
