/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:58 by migumore          #+#    #+#             */
/*   Updated: 2024/10/04 14:33:22 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	no_imput_exit(t_data *data)
{
	free(data->prompt);
	ft_free_array(data->env);
	ft_free_array(data->path);
	ft_free_lst(data);
	printf("exit\n");
	exit(0);
}

static void	parser_to_executor(t_data *data)
{
	data->commands = ft_split_input(data->input);
	if (data->commands && ft_strcmp(data->commands[0], "\0"))
	{
		data->list = ft_prepare_list(data);
		if (data->list->args)
			execute(data);
	}
	else
		ft_free_array(data->commands);
}

void	read_input(t_data *data)
{
	while (1)
	{
		//set_prompt(data);
		data->prompt = ft_strdup("minishell % ");
		data->input = readline(data->prompt);
		add_history(data->input);
		if (!data->input)
			no_imput_exit(data);
		else if (check_input(data->input))
		{
			printf("syntax error near unexpected token\n");
			free(data->input);
		}
		else
			parser_to_executor(data);
		ft_free_lst(data);
		if (data->prompt)
			free(data->prompt);
	}
}
