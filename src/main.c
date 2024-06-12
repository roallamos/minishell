/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:12:44 by migumore          #+#    #+#             */
/*   Updated: 2024/06/12 17:22:02 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler(int signal)
 {
	if (signal == SIGINT)
 	{
 		ft_putchar_fd('\n', STDOUT);
 		rl_on_new_line();
 		rl_replace_line("", 1);
 		rl_redisplay();
 	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data				data;
	struct sigaction	sa;

	(void)argv;
	(void)envp;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	if (argc > 1)
	{
		ft_putendl_fd("Only 1 argument required", STDERR);
		return (EXIT_SUCCESS);
	}
	while (1)
	{
		data.input = readline(CYAN BOLD"minishell:~$"RESET);
		if (!data.input)
		{
			printf("exit\n");
			return (EXIT_SUCCESS);
		}
		free(data.input);
	}
	return (0);
}
