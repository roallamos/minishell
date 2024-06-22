/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:58 by migumore          #+#    #+#             */
/*   Updated: 2024/06/22 15:40:23 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	read_input(t_data *data)
{
	while (1)
	{
		data->input = readline(CYAN BOLD"minishell:~$ "RESET);
		if (!data->input)
		{
			printf("exit\n");
			ft_free_path(data);
			ft_free_env(data);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		if (*data->input)
			add_history(data->input);
		data->args = ft_split_input(data->input, data);
		parse(data);
		data->pids = fork();
		if (data->pids == 0)
			get_cmd_and_execute(data);
		else
			waitpid(data->pids, &data->status, 0);
		ft_free_args(data);
		free(data->input);
	}
}
