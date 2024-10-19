/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:58 by migumore          #+#    #+#             */
/*   Updated: 2024/10/19 18:01:33 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parser_to_executor(t_data *data, int is_piped)
{
	data->commands = ft_split_input(data->input, data);
	if (data->commands && ft_strcmp(data->commands[0], "\0"))
	{
		data->list = ft_prepare_list(data);
		if (data->list->args)
		{
			execute(data, is_piped);
			close_files(data->list);
		}
	}
	else
		ft_free_array((void **)data->commands);
}

void	verify_input(t_data *data, int is_piped)
{
	if (check_input(data->input, data))
	{
		printf("syntax error near unexpected token\n");
		g_exit_status = 2;
		free(data->input);
	}
	else if (!only_spaces(data->input))
		parser_to_executor(data, is_piped);
	else
		free(data->input);
	ft_free_lst(data);
	data->d_quote = 0;
	data->s_quote = 0;
}

void	read_input(t_data *data, int is_piped)
{
	while (1)
	{
		signal(SIGINT, handler);
		data->stop_exec_hd = 0;
		if (!is_piped)
			data->input = readline("minishell$ ");
		else
			data->input = get_next_line(STDIN);
		add_history(data->input);
		if (!data->input)
			do_exit(data, 0, is_piped);
		else
			verify_input(data, is_piped);
	}
}
