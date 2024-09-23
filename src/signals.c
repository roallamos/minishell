/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:31:52 by migumore          #+#    #+#             */
/*   Updated: 2024/09/23 14:01:15 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
