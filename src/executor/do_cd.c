/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:54:45 by migumore          #+#    #+#             */
/*   Updated: 2024/07/01 18:38:48 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_cd(t_data *data, int pos)
{
	int		res;
	char	*home;
	char	*user;

	if (data->list->args[pos + 1] && (*data->list->args[pos + 1] != '~'))
		res = chdir(data->list->args[pos + 1]);
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
