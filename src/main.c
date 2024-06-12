/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:12:44 by migumore          #+#    #+#             */
/*   Updated: 2024/06/12 18:01:06 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_data				data;

	(void)argv;
	(void)envp;
	signals();
	if (argc > 1)
	{
		ft_putendl_fd("Only 1 argument required", STDERR);
		return (EXIT_SUCCESS);
	}
	while (1)
	{
		data.input = readline(CYAN BOLD"minishell:~$"RESET);
		add_history(data.input);
		if (!data.input)
		{
			printf("exit\n");
			return (EXIT_SUCCESS);
		}
		free(data.input);
	}
	return (0);
}
