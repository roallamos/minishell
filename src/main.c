/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:12:44 by migumore          #+#    #+#             */
/*   Updated: 2024/10/09 21:41:19 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

unsigned char	g_exit_status = 0;

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1)
	{
		ft_putendl_fd("Only 1 argument required", STDERR);
		return (EXIT_SUCCESS);
	}
	ft_memset(&data, 0, sizeof(t_data));
	dup_env(&data, env);
	get_pwd(&data);
	read_input(&data);
	return (0);
}
