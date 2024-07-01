/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/07/01 16:50:01 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_var(t_data *data, int pos)
{
	char	*temp;

	temp = data->commands[pos];
	data->commands[pos] = getenv(&data->commands[pos][1]);
	free(temp);
}

static void	check_builtin(t_data *data, int pos)
{
	if (!ft_strcmp(data->list->args[pos], "export"))
		export(data, pos);
	else if (!ft_strcmp(data->list->args[pos], "env"))
		print_env(data);
	else if (!ft_strcmp(data->list->args[pos], "exit"))
		do_exit(data);
	else if (!ft_strcmp(data->list->args[pos], "pwd"))
		printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strcmp(data->list->args[pos], "cd"))
		do_cd(data, pos);
}

void	parse(t_data *data)
{
	int	i;

	i = 0;
	//check_tokens(data);
	while (data->commands[i])
	{
		if (!data->commands[i][0])
			return ;
		else if (data->commands[i][0] == '$')
			expand_var(data, i);
		else
			check_builtin(data, i); //aqui hay un segfault tambien
		i++;
	}
	data->cmd_pos = i;
}
