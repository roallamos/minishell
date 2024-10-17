/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:42:08 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/17 17:23:51 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_echo_flag(char **args, int *new_line)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	while (args && args[i])
	{
		f = 0;
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '-' && f == 0 && ft_strcmp(args[i], "-"))
				f = 1;
			else if (args[i][j] != 'n' || (args[i][j] == 'n' && j == 0))
				return (&args[i]);
			j++;
		}
		if (!args[i][j] && f == 1)
			*new_line = 0;
		i++;
	}
	return (&args[i]);
}

void	do_echo(t_data *data)
{
	char	**print;
	int		i;
	int		new_line;

	i = 0;
	new_line = 1;
	print = check_echo_flag(&data->list->args[1], &new_line);
	while (print[i])
	{
		printf("%s", print[i++]);
		if (print[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}
