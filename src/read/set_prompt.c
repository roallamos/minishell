/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:25:46 by migumore          #+#    #+#             */
/*   Updated: 2024/09/27 10:46:14 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*cut_domain(char *hn)
{
	int		len;
	char	*tmp;

	len = 0;
	if (hn)
	{
		while (hn[len])
		{
			if (hn[len] == '.')
				break ;
			len++;
		}
		tmp = (char *)ft_calloc(sizeof(char), len + 1);
		len--;
		while (len >= 0)
		{
			tmp[len] = hn[len];
			len--;
		}
		tmp = ft_strjoin_free(tmp, ":");
		return (tmp);
	}
	return (NULL);
}

static void	null_term(char *hn, ssize_t bytes_read)
{
	if (bytes_read > 0 && hn[bytes_read - 1] == '\n')
	{
		hn[bytes_read - 1] = '\0';
	}
	else
	{
		hn[bytes_read] = '\0';
	}
}

char	*get_hostname(void)
{
	int		fd;
	char	*hn;
	char	*tmp;
	ssize_t	bytes_read;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	hn = (char *)malloc(HOSTNAME_MAX_LEN);
	bytes_read = read(fd, hn, HOSTNAME_MAX_LEN - 1);
	if (bytes_read == -1)
	{
		perror("read");
		close(fd);
		return (NULL);
	}
	close(fd);
	null_term(hn, bytes_read);
	tmp = cut_domain(hn);
	free(hn);
	return (tmp);
}

static char	*put_tilde(t_data *data, char *user)
{
	char	*cu;
	int		len;

	if (data->pwd)
		free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	cu = ft_strjoin("/home/", user);
	len = ft_strlen(cu);
	if (ft_strncmp(cu, data->pwd, len) == 0)
	{
		free(cu);
		cu = ft_strjoin("~", data->pwd + len);
		return (cu);
	}
	return (data->pwd);
}

void	set_prompt(t_data *data)
{
	char	*user;
	char	*hostname;
	char	*current_dir;

	user = getenv("USER");
	if (data->prompt)
		free(data->prompt);
	data->prompt = ft_strjoin(BOLD_GREEN, user);
	data->prompt = ft_strjoin_free(data->prompt, "@");
	if (!data->prompt)
		return ;
	hostname = get_hostname();
	data->prompt = ft_strjoin_free(data->prompt, hostname);
	free(hostname);
	if (!data->prompt)
		return ;
	current_dir = put_tilde(data, user);
	data->prompt = ft_strjoin_free(data->prompt, BOLD_YELLOW);
	data->prompt = ft_strjoin_free(data->prompt, current_dir);
	free(current_dir);
	if (!data->prompt)
		return ;
	data->prompt = ft_strjoin_free(data->prompt, BOLD_WHITE"$ "RESET);
	if (!data->prompt)
		return ;
}
