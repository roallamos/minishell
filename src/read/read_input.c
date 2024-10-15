/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:58 by migumore          #+#    #+#             */
/*   Updated: 2024/10/15 18:33:43 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	no_input_exit(t_data *data)
{
	free(data->prompt);
	ft_free_array((void **)data->env);
	ft_free_array((void **)data->path);
	ft_free_lst(data);
	printf("exit\n");
	exit(0);
}

static void	parser_to_executor(t_data *data)
{
	data->commands = ft_split_input(data->input, data);
	if (data->commands && ft_strcmp(data->commands[0], "\0"))
	{
		data->list = ft_prepare_list(data);
		if (data->list->args)
			execute(data);
	}
	else
		ft_free_array((void **)data->commands);
}

void	read_input(t_data *data)
{
	while (1)
	{
		signal(SIGINT, handler);
		data->stop_exec = 0;
		data->prompt = ft_strdup("minishell$ ");
		data->input = readline(data->prompt);
		add_history(data->input);
		if (!data->input)
			no_input_exit(data);
		else if (check_input(data->input, data))
		{
			printf("syntax error near unexpected token\n");
			g_exit_status = 2;
			free(data->input);
		}
		else if (!only_spaces(data->input))
			parser_to_executor(data);
		else
			free(data->input);
		ft_free_lst(data);
		if (data->prompt)
			free(data->prompt);
		data->d_quote = 0;
		data->s_quote = 0;
	}
}
