/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:31 by migumore          #+#    #+#             */
/*   Updated: 2024/07/11 18:30:52 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	here_doc(t_data *data, int i)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, data->list->heredoc[i],
				ft_strlen(data->list->heredoc[i])) == 0)
			break ;
		write(data->fd_heredoc, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(data->fd_heredoc);
	data->fd_heredoc = open("here_doc", O_RDONLY);
	if (data->fd_heredoc < 0)
		write_error("pipex: No such file or directory: ", "here_doc");
}

void	infile(t_data *data, int i)
{
	data->fd_infile = open(data->list->infile[i], O_RDONLY);
	if (data->fd_infile < 0)
	{
		write_error("minishell: No such file or directory: ",
			data->list->infile[i]);
		exit(1);
	}
}

void	heredoc(t_data *data, int i)
{
	data->fd_heredoc = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd_heredoc < 0)
	{
		write_error("minishell: No such file or directory: ", "here_doc");
		unlink("here_doc");
	}
	here_doc(data, i);
}

void	outfile(t_data *data, int i)
{
	data->fd_outfile = open(data->list->outfile[i], O_CREAT | O_RDWR
			| O_TRUNC, 0644);
	if (data->fd_outfile < 0)
		write_error("minishell: No such file or directory: ",
			data->list->outfile[i]);
}

void	append(t_data *data, int i)
{
	data->fd_append = open(data->list->append[i], O_CREAT | O_RDWR
			| O_APPEND, 0644);
	if (data->fd_append < 0)
		write_error("minishell: No such file or directory: ",
			data->list->append[i]);
}

void	check_redirs(t_data *data)
{
	int	i;

	i = 0;
	if (data->list->heredoc || data->list->infile || data->list->append
		|| data->list->outfile)
	{
		if (data->list->heredoc)
		{
			while (data->list->heredoc[i])
			{
				if (data->fd_heredoc)
					close(data->fd_heredoc);
				here_doc(data, i++);
			}
		}
		i = 0;
		if (data->list->infile)
		{
			while (data->list->infile[i])
			{
				if (data->fd_infile)
					close(data->fd_infile);
				infile(data, i++);
			}
		}
		i = 0;
		if (data->list->append)
		{
			while (data->list->append[i])
			{
				if (data->fd_append)
					close(data->fd_append);
				append(data, i++);
			}
		}
		i = 0;
		if (data->list->outfile)
		{
			while (data->list->outfile[i])
			{
				if (data->fd_outfile)
					close(data->fd_outfile);
				infile(data, i++);
			}
		}
	}
}
