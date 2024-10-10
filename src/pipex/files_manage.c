/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:31 by migumore          #+#    #+#             */
/*   Updated: 2024/10/10 15:35:02 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	append(t_data *data, int i)
{
	if (access(data->list->docs[i].doc, W_OK) == -1)
	{
		write_error("minishell: Permission denied: ",
			data->list->docs[i].doc);
		return (1);
	}
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_CREAT | O_WRONLY
			| O_APPEND, 0644);
	if (data->list->docs[i].fd < 0)
	{
		write_error("minishell: No such file or directory: ",
			data->list->docs[i].doc);
		return (1);
	}
	return (0);
}

int	outfile(t_data *data, int i)
{
	if (access(data->list->docs[i].doc, W_OK) == -1)
	{
		write_error("minishell: Permission denied: ",
			data->list->docs[i].doc);
		return (1);
	}
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_CREAT | O_WRONLY
			| O_TRUNC, 0644);
	if (data->list->docs[i].fd < 0)
	{
		write_error("minishell: No such file or directory: ",
			data->list->docs[i].doc);
		return (1);
	}
	return (0);
}

static void	write_here_doc(t_data *data, char	*limiter, int i)
{
	char	**line;
	int		lim_len;

	lim_len = ft_strlen(limiter);
	line = ft_calloc(2, sizeof(char *));
	g_exit_status = 0;
	while (1)
	{
		line[0] = readline("> ");
		if (!line[0])
			break ;
		line[0] = ft_strjoin_free(line[0], "\n");
		if (g_exit_status == 130)
			data->stop_exec = 1;
		if (ft_strncmp(line[0], limiter, lim_len) == 0 || g_exit_status == 130)
			break ;
		if (data->list->docs[i].exp)
			heredock_expansor(line, data);
		write(data->list->docs[i].fd, line[0], ft_strlen(line[0]));
		free(line[0]);
	}
	ft_free_array(line);
	free(limiter);
}

void	heredoc(t_data *data, int i)
{
	char	*limiter;

	limiter = ft_strjoin_free(data->list->docs[i].doc, "\n");
	open_tmp_file(data, i);
	write_here_doc(data, limiter, i);
	close(data->list->docs[i].fd);
	infile(data, i);
}

int	infile(t_data *data, int i)
{
	if (access(data->list->docs[i].doc, R_OK) == -1)
	{
		write_error("minishell: Permission denied: ",
			data->list->docs[i].doc);
		return (1);
	}
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_RDONLY);
	if (data->list->docs[i].fd < 0)
	{
		write_error("minishell: No such file or directory: ",
			data->list->docs[i].doc);
		return (1);
	}
	return (0);
}
