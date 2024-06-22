/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:54:45 by migumore          #+#    #+#             */
/*   Updated: 2024/06/22 20:16:19 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_cd(t_data *data, int pos)
{
	int		res;
	char	*home;
	char	*user;

	if (data->args[pos + 1] && (*data->args[pos + 1] != '~'))
		res = chdir(data->args[pos + 1]);
	else
	{
		user = getenv("USER");
		home = ft_strjoin("/home/", user);
		res = chdir(home);
		free(home);
	}
	if (res == -1)
		perror("cd");
}
