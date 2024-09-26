/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:31:52 by migumore          #+#    #+#             */
/*   Updated: 2024/09/26 18:16:53 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler(int signal)
{
	unsigned char c_signal = 130;
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = g_exit_status & 0;
		g_exit_status = g_exit_status | c_signal;
	}
}
/*void	handle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}*/
