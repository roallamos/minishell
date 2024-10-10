/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:59:37 by migumore          #+#    #+#             */
/*   Updated: 2024/10/10 22:55:39 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_files(t_data *data)
{
	int		i;
	t_cmd	*tmp;

	tmp = data->list;
	while (data->list)
	{
		i = 0;
		while (data->list->docs && data->list->docs[i].doc)
		{
			if (data->list->docs[i].fd > 0)
				close(data->list->docs[i].fd);
			i++;
		}
		data->list = data->list->next;
	}
	data->list = tmp;
}

void	open_tmp_file(t_data *data, int i)
{
	static int	count = 0;
	char		*nbr;

	data->list->docs[i].doc = ft_strdup(HD_PREFIX);
	nbr = ft_itoa(count);
	data->list->docs[i].doc = ft_strjoin_free(data->list->docs[i].doc, nbr);
	free(nbr);
	if (access(data->list->docs[i].doc, F_OK) == 0)
	{
		free(data->list->docs[i].doc);
		count++;
		open_tmp_file(data, i);
	}
	data->list->docs[i].fd = open(data->list->docs[i].doc, O_CREAT | O_RDWR
			| O_TRUNC, 0644);
	if (data->list->docs[i].fd < 0)
	{
		write_error("minishell: No such file or directory: ",
			data->list->docs[i].doc);
		unlink(data->list->docs[i].doc);
	}
	count++;
}

void	delete_here_docs(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	i = 0;
	tmp = data->list;
	while (i < data->num_commands)
	{
		j = 0;
		while (data->list->docs && data->list->docs[j].doc)
		{
			if (data->list->docs[j].flag == 1)
				unlink(data->list->docs[j].doc);
			j++;
		}
		data->list = data->list->next;
		i++;
	}
	data->list = tmp;
}

void	wait_pids(t_data *data, int i)
{
	while (i < data->num_commands)
	{
		if (i == data->num_commands - 1)
			waitpid(data->pids[i], &data->status, 0);
		else
			waitpid(data->pids[i], NULL, 0);
		i++;
	}
	if (WIFEXITED(data->status))
		g_exit_status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		g_exit_status = WTERMSIG(data->status) + 128;
}
