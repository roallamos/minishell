/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/24 18:41:56 by migumore         ###   ########.fr       */
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
	if (!ft_strcmp(data->commands[pos], "export"))
		export(data, pos);
	else if (!ft_strcmp(data->commands[pos], "env"))
		print_env(data);
	else if (!ft_strcmp(data->commands[pos], "exit"))
		do_exit(data);
	else if (!ft_strcmp(data->commands[pos], "pwd"))
		printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strcmp(data->commands[pos], "cd"))
		do_cd(data, pos);
}

void	parse(t_data *data)
{
	int	i;

	i = 0;
	while (data->commands[i])
	{
		if (!data->commands[i][0])
			return ;
		else if (data->commands[i][0] == '$')
			expand_var(data, i);
		else
			check_builtin(data, i);
		i++;
	}
	data->cmd_pos = i;
}
