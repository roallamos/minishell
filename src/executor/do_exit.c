/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:14:44 by migumore          #+#    #+#             */
/*   Updated: 2024/06/22 19:36:29 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_exit(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->prompt)
		free(data->prompt);
	ft_free_args(data);
	ft_free_path(data);
	ft_free_env(data);
	rl_clear_history();
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
