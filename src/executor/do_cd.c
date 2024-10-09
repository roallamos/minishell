/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:54:45 by migumore          #+#    #+#             */
/*   Updated: 2024/10/09 21:11:58 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_pwd_n_oldpwd(t_data *data, char *pwd, char *oldpwd)
{
	int		i;
	int		j;
	int		k;
	char	*cwd;

	i = 0;
	j = -1;
	k = -1;
	if (data->env)
	{
		while (data->env[i])
		{
			if (ft_strncmp(data->env[i], pwd, ft_strlen(pwd)) == 0)
				j = i;
			if (ft_strncmp(data->env[i], oldpwd, ft_strlen(oldpwd)) == 0)
				k = i;
			i++;
		}
		if (j >= 0 && k >= 0 && data->env[k])
		{
			free(data->env[k]);
			data->env[k] = ft_strjoin("OLDPWD=", data->env[j] + 4);
		}
		if (j >= 0 && k >= 0 && data->env[j])
		{
			free(data->env[j]);
			cwd = getcwd(NULL, 0);
			data->env[j] = ft_strjoin("PWD=", cwd);
			free(cwd);
			if (!data->env[j])
				data->env[j] = ft_strjoin("PWD=", data->env[k] + 7);
		}
	}
	get_pwd(data);
}

int		array_length(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

void	do_cd(t_data *data, int pos)
{
	int		res;
	char	*home;
	char	*user;

	res = 0;
	if (array_length(data->list->args) > 2)
		printf("too many arguments\n");
	else if (data->list->args[pos + 1] && (*data->list->args[pos + 1] != '~'
		&& *data->list->args[pos + 1] != '-'))
		res = chdir(data->list->args[pos + 1]);
	else if (data->list->args[pos + 1] && (*data->list->args[pos + 1] == '~'))
	{
		user = getenv("USER");
		home = ft_strjoin("/home/", user);
		res = chdir(home);
		free(home);
	}
	else if (data->list->args[pos + 1] && (*data->list->args[pos + 1] == '-'))
	{
		if (data->oldpwd)
			res = chdir(data->oldpwd);
		else
			printf("OlDPWD is not set\n");
	}
	if (res == -1)
		perror("cd");
	else
		update_pwd_n_oldpwd(data, "PWD", "OLDPWD");
}
