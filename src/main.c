/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:12:44 by migumore          #+#    #+#             */
/*   Updated: 2024/06/19 19:38:47 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_cmd_and_execute(t_data *data, char *envp[])
{
	data->args = ft_split_command(data->input, data);
	parse(data);
	data->cmd = ft_get_cmd(data->path, data->args[0]);
	if (!data->cmd)
	{
		write_error("minishell: command not found: ", data->args[0]);
		ft_free_args(data);
		ft_free_path(data);
		exit(127);
	}
	execve(data->cmd, data->args, envp);
	perror("execve");
	exit(1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
//	char	*pwd;

	(void)argv;
	(void)envp; 
	signal(SIGINT, handler);
//	pwd = getcwd(NULL, 0);
//	printf("%s\n", pwd);
//	free (pwd);
	if (argc > 1)
	{
		ft_putendl_fd("Only 1 argument required", STDERR);
		return (EXIT_SUCCESS);
	}
	while (1)
	{
		data.input = readline(CYAN BOLD"minishell:~$ "RESET);
		add_history(data.input);
		if (!data.input)
		{
			printf("exit\n");
			return (EXIT_SUCCESS);
		}
		data.envp = envp;
		data.path_envp = ft_find_path(envp);
		data.path = ft_split(data.path_envp, ':');
		data.pids = fork();
		if (data.pids == 0)
			get_cmd_and_execute(&data, envp);
		else
			waitpid(data.pids, &data.status, 0);
		free(data.input);
	}
	return (0);
}
