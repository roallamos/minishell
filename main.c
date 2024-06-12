/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:51:01 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/12 16:09:04 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	handler(int signal)
{
	//if (signal == SIGINT)
	//	kill(0, SIGINT);
}*/

int	main(void)
{
	/*struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	while (1)
		pause();*/
	printf(GREEN"minishell");
	return (0);
}
