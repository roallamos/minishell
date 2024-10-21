/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:14:44 by migumore          #+#    #+#             */
/*   Updated: 2024/10/21 16:19:02 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_args_aux(t_data *data, int *j, int i)
{
	*j = 0;
	while (ft_isspace(data->list->args[i][*j]))
		(*j)++;
	if (data->list->args[i][*j] == '+' || data->list->args[i][*j] == '-')
		(*j)++;
	while (ft_isdigit(data->list->args[i][*j]))
		(*j)++;
	while (ft_isspace(data->list->args[i][*j]))
		(*j)++;
}

static int	check_args(t_data *data)
{
	int			i;
	int			j;
	long long	nb;

	i = 0;
	while (data->list && data->list->args[i])
	{
		if (i == 1)
		{
			check_args_aux(data, &j, i);
			if (data->list->args[i][j] || ft_atoll(data->list->args[i], &nb))
			{
				write_error("minishell: exit: numeric argument required: ",
					data->list->args[i]);
				return (2);
			}
		}
		else if (i > 1)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		i++;
	}
	return (0);
}

int	do_exit(t_data *data, int in_child, int is_piped)
{
	int	exit_status;

	if (!in_child && !is_piped)
		printf("exit\n");
	if (data->file_fd != -1)
		close(data->file_fd);
	exit_status = check_args(data);
	if (!exit_status && data->list && data->list->args[1])
		exit_status = ft_atoi(data->list->args[1]);
	else if (exit_status == 0)
		exit_status = g_exit_status;
	else if (exit_status == 1)
	{
		g_exit_status = exit_status;
		return (1);
	}
	ft_free_all(data);
	exit(exit_status);
}
