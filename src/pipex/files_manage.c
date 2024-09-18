/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:31 by migumore          #+#    #+#             */
/*   Updated: 2024/09/18 13:08:35 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	append(t_data *data, int i)
{
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_CREAT | O_RDWR
			| O_APPEND, 0644);
	if (data->list->docs[i].fd < 0)
		write_error("minishell: No such file or directory: ",
			data->list->docs[i].doc);
}

void	outfile(t_data *data, int i)
{
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_CREAT | O_RDWR
			| O_TRUNC, 0644);
	if (data->list->docs[i].fd < 0)
		write_error("minishell: No such file or directory: ",
			data->list->docs[i].doc);
}

static void	write_here_doc(t_data *data, int i)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(data->list->docs[i].doc, "\n");
	printf("%s", limiter);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter,
				ft_strlen(limiter)) == 0)
			break ;
		write(data->list->docs[i].fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(limiter);
	close(data->list->docs[i].fd);
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_RDONLY);
	if (data->list->docs[i].fd < 0)
		write_error("pipex: No such file or directory: ", "here_doc");
}

void	heredoc(t_data *data, int i)
{
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_CREAT | O_RDWR
			| O_TRUNC, 0644);
	if (data->list->docs[i].fd < 0)
	{
		write_error("minishell: No such file or directory: ", "here_doc");
		unlink(data->list->docs[i].doc);
	}
	write_here_doc(data, i);
}

void	infile(t_data *data, int i)
{
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_RDONLY);
	if (data->list->docs[i].fd < 0)
		write_error("minishell: No such file or directory: ",
			data->list->docs[i].doc);
}

void	check_redirs(t_data *data)
{
	int		i;
	t_cmd	*tmp;

	tmp = data->list;
	while (data->list)
	{
		i = 0;
		while (data->list->docs && data->list->docs[i].doc)
		{
			printf("flag=%i en i=%i\n", data->list->docs->flag, i);
			if (data->list->docs->flag == 0)
				infile(data, i);
			if (data->list->docs->flag == 1)
				heredoc(data, i);
			if (data->list->docs->flag == 2)
				outfile(data, i);
			if (data->list->docs->flag == 3)
				append(data, i);
			printf("nombre: %s\ntipo: %i\nfd: %i\ni: %i\n", data->list->docs[i].doc, data->list->docs[i].flag, data->list->docs[i].fd, i);
			i++;
		}
		data->list = data->list->next;
	}
	data->list = tmp;
}
