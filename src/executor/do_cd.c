/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:54:45 by migumore          #+#    #+#             */
/*   Updated: 2024/10/07 11:28:56 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_pwd_n_oldpwd(char *env[], char *pwd, char *oldpwd)
{
	int		i;
	int		j;
	int		k;
	char	*cwd;

	i = 0;
	j = 0;
	if (env)
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], pwd, ft_strlen(pwd)) == 0)
				j = i;
			if (ft_strncmp(env[i], oldpwd, ft_strlen(oldpwd)) == 0)
				k = i;
			i++;
		}
		free(env[k]);
		env[k] = ft_strjoin("OLDPWD=", env[j] + 4);
		free(env[j]);
		cwd = getcwd(NULL, 0);
		env[j] = ft_strjoin("PWD=", cwd);
		if (!env[j])
			env[j] = ft_strjoin("PWD=", env[k] + 7);
	}
}

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
	update_pwd_n_oldpwd(data->env, "PWD", "OLDPWD");
}
