/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:12:44 by migumore          #+#    #+#             */
/*   Updated: 2024/10/07 13:42:00 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

unsigned char	g_exit_status = 0;

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	(void)argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1)
	{
		ft_putendl_fd("Only 1 argument required", STDERR);
		return (EXIT_SUCCESS);
	}
	ft_memset(&data, 0, sizeof(t_data));
	dup_env(&data, env);
	read_input(&data);
	return (0);
}
