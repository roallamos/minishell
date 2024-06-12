/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:41:49 by rodralva          #+#    #+#             */
/*   Updated: 2024/02/21 18:13:41 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_stc(char *stc)
{
	int		i;
	size_t	len;

	i = 0;
	while (stc[i] && stc[i] != '\n')
		i++;
	if (stc[i])
		i++;
	len = ft_strlen(stc + i);
	stc = ft_memmove(stc, stc + i, len);
	stc[len] = '\0';
}

static char	*ft_read(int fd, char *stc, char *ret)
{
	int		bytes;

	bytes = 1;
	while (ft_strchr_null(ret, '\n') == 0 && bytes > 0)
	{
		bytes = read(fd, stc, BUFFER_SIZE);
		if (bytes < 0)
		{
			free (ret);
			stc[0] = '\0';
			return (0);
		}
		stc[bytes] = '\0';
		if (bytes != 0)
			ret = ft_strjoin_free(ret, stc);
	}
	ft_stc(stc);
	return (ret);
}

static char	*ft_ret(char *stc)
{
	int		i;
	char	*ret;

	i = 0;
	while (stc[i] != '\n')
		i++;
	ret = ft_substr(stc, 0, i + 1);
	return (ret);
}

static char	*ft_retjoin(char *stc)
{
	char	*ret;

	if (ft_strchr_null(stc, '\n'))
	{
		ret = ft_ret(stc);
		ft_stc(stc);
	}
	else
		ret = ft_strdup(stc);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	stc[BUFFER_SIZE + 1];
	char		*ret;
	int			i;

	i = 0;
	ret = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (*stc)
		ret = ft_retjoin(stc);
	if (ft_strchr_null(ret, '\n'))
		return (ret);
	ret = ft_read(fd, stc, ret);
	if (!ret)
		return (NULL);
	while (ret[i] && ret[i] != '\n')
		i++;
	if (ret[i])
		i++;
	ret[i] = '\0';
	return (ret);
}
