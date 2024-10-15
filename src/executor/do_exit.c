/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:14:44 by migumore          #+#    #+#             */
/*   Updated: 2024/10/15 08:07:19 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_exit(t_data *data)
{
	int	exit_status;

	printf("exit\n");
	exit_status = ft_atoi(data->list->args[1]);
	free(data->prompt);
	ft_free_array((void **)data->env);
	ft_free_array((void **)data->path);
	ft_free_lst(data);
	if (exit_status != 0)
		exit(exit_status);
	else
		exit(EXIT_SUCCESS);
}
