/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:14:44 by migumore          #+#    #+#             */
/*   Updated: 2024/09/19 13:50:37 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_exit(t_data *data)
{
	int	exit_status;

	printf("exit\n");
	exit_status = ft_atoi(data->list->args[1]);
	if (exit_status != 0)
		exit(exit_status);
	else
		exit(EXIT_SUCCESS);
}
