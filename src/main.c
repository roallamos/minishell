/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:12:44 by migumore          #+#    #+#             */
/*   Updated: 2024/06/12 17:14:10 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	handler(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		ft_putchar_fd('\n', STDOUT);
// 		rl_on_new_line();
// 		rl_replace_line("", 1);
// 		rl_redisplay();
// 	}
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_data				data;

	(void)argv;
	(void)envp;
	if (argc > 1)
	{
		ft_putendl_fd("Only 1 argument required", STDERR);
		return (EXIT_SUCCESS);
	}
	while (1)
	{
		printf(CYAN BOLD"minishell:~$"RESET);
		data.input = readline(NULL);
		if (!data.input)
		{
			printf("exit\n");
			return (EXIT_SUCCESS);
		}
	}
	return (0);
}
