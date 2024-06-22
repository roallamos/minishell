/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/22 20:15:41 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_var(t_data *data, int pos)
{
	char	*temp;

	temp = data->args[pos];
	data->args[pos] = getenv(&data->args[pos][1]);
	free(temp);
}

void	parse(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		if (!data->args[i][0])
			return ;
		else if (data->args[i][0] == '$')
			expand_var(data, i);
		else if (!ft_strcmp(data->args[i], "export"))
			export(data, i);
		else if (!ft_strcmp(data->args[i], "env"))
			print_env(data);
		else if (!ft_strcmp(data->args[i], "exit"))
			do_exit(data);
		else if (!ft_strcmp(data->args[i], "pwd"))
			printf("%s\n", getcwd(NULL, 0));
		else if (!ft_strcmp(data->args[i], "cd"))
			do_cd(data, i);
		i++;
	}
}
