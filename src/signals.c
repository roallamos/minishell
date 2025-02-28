/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:31:52 by migumore          #+#    #+#             */
/*   Updated: 2024/10/07 11:27:08 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler(int signal)
{
	unsigned char	c_signal;

	c_signal = 130;
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		ioctl(STDIN, TIOCSTI, "\n");
		g_exit_status = g_exit_status & 0;
		g_exit_status = g_exit_status | c_signal;
	}
}
