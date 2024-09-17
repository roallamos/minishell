/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:31 by migumore          #+#    #+#             */
/*   Updated: 2024/09/17 15:27:21 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void	here_doc(t_data *data)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = get_next_line(STDIN_FILENO);
// 		if (ft_strncmp(line, data->list->heredoc,
// 				ft_strlen(data->list->heredoc)) == 0)
// 			break ;
// 		write(data->list->fd_heredoc, line, ft_strlen(line));
// 		free(line);
// 	}
// 	free(line);
// 	close(data->list->fd_heredoc);
// 	data->list->fd_heredoc = open("here_doc", O_RDONLY);
// 	if (data->list->fd_heredoc < 0)
// 		write_error("pipex: No such file or directory: ", "here_doc");
// }

// void	heredoc(t_data *data)
// {
// 	data->list->fd_heredoc = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (data->list->fd_heredoc < 0)
// 	{
// 		write_error("minishell: No such file or directory: ", "here_doc");
// 		unlink("here_doc");
// 	}
// 	here_doc(data);
// }

// void	infile(t_data *data)
// {
// 	data->list->fd_infile = open(data->list->infile, O_RDONLY);
// 	if (data->list->fd_infile < 0)
// 	{
// 		write_error("minishell: No such file or directory: ",
// 			data->list->infile);
// 		exit(1);
// 	}
// }

// void	outfile(t_data *data)
// {
// 	data->list->fd_outfile = open(data->list->outfile, O_CREAT | O_RDWR
// 			| O_TRUNC, 0644);
// 	if (data->list->fd_outfile < 0)
// 		write_error("minishell: No such file or directory: ",
// 			data->list->outfile);
// }

// void	append(t_data *data)
// {
// 	data->list->fd_append = open(data->list->append, O_CREAT | O_RDWR
// 			| O_APPEND, 0644);
// 	if (data->list->fd_append < 0)
// 		write_error("minishell: No such file or directory: ",
// 			data->list->append);
// }

// void	check_redirs(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->list->docs && data->list->docs[i])
// 	{
// 		if (data->list->docs->flag == 0)
// 			infile(data);
// 		if (data->list->docs->flag == 1)
// 			here_doc(data);
// 		if (data->list->docs->flag == 2)
// 			outfile(data);
// 		if (data->list->docs->flag == 3)
// 			append(data);
// 		i++;
// 	}
// }
