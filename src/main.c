/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:12:44 by migumore          #+#    #+#             */
/*   Updated: 2024/10/19 18:24:03 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

unsigned char	g_exit_status = 0;

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;
	int		is_piped;

	signal(SIGQUIT, SIG_IGN);
	ft_memset(&data, 0, sizeof(t_data));
	get_pwd(&data);
	dup_env(&data, env);
	data.file_fd = -1;
	is_piped = !isatty(STDIN_FILENO);
	if (argc > 1)
		return (execute_file(argv[1], &data));
	else
		read_input(&data, is_piped);
	return (0);
}
