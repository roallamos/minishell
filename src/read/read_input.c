/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:58 by migumore          #+#    #+#             */
/*   Updated: 2024/06/21 19:23:25 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	read_input(t_data *data)
{
	while (1)
	{
		data->input = readline(CYAN BOLD"minishell:~$ "RESET);
		add_history(data->input);
		if (!data->input)
		{
			printf("exit\n");
			ft_free_path(data);
			exit(EXIT_SUCCESS);
		}
		data->args = ft_split_input(data->input, data);
		parse(data);
		data->pids = fork();
		if (data->pids == 0)
			get_cmd_and_execute(data);
		else
			waitpid(data->pids, &data->status, 0);
		free(data->input);
	}
}
