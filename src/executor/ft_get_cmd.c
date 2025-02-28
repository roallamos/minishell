/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:34:45 by migumore          #+#    #+#             */
/*   Updated: 2024/10/10 20:37:53 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_get_cmd(char **path, char *cmd)
{
	int		i;
	char	*temp;
	char	*cmd_path;

	if (cmd && ft_strchr(cmd, '/'))
	{
		if (access(cmd, 0) == 0)
			return (ft_strdup(cmd));
	}
	else if (path)
	{
		i = 0;
		while (path[i])
		{
			temp = ft_strjoin(path[i], "/");
			cmd_path = ft_strjoin(temp, cmd);
			free(temp);
			if (access(cmd_path, 0) == 0 && *cmd)
				return (cmd_path);
			free(cmd_path);
			i++;
		}
	}
	return (NULL);
}
