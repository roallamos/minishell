/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:49:39 by migumore          #+#    #+#             */
/*   Updated: 2024/10/21 12:47:49 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(char *filename, t_data *data)
{
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == -1)
		{
			write_error("minishell: Permission denied: ", filename);
			return (126);
		}
	}
	data->file_fd = open(filename, O_RDONLY);
	if (data->file_fd < 0)
	{
		write_error("minishell: No such file or directory: ", filename);
		return (127);
	}
	return (0);
}

int	execute_file(char *filename, t_data *data)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = open_file(filename, data);
	if (!ret)
	{
		line = get_next_line(data->file_fd);
		while (line != NULL)
		{
			data->input = line;
			verify_input(data, 1);
			line = get_next_line(data->file_fd);
		}
	}
	if (data->file_fd > -1)
		close(data->file_fd);
	ft_free_array((void **)data->env);
	ft_free_array((void **)data->path);
	free(data->pwd);
	free(data->oldpwd);
	if (ret)
		return (ret);
	return (g_exit_status);
}
