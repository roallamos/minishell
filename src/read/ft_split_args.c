
#include <minishell.h>

/*static int  advance_quotes(const char *s)
{
    char quote;
    int i;

    i = 0;
    quote = s[i++];
    while (s[i] && s[i] != quote)
        i++;
    if (s[i])
	{
        i++;
		if (s[i] && (s[i] == '\'' || s[i] == '"'))
			i += advance_quotes(&s[i]);
	}
    return (i);
}

static char	**ft_free(char **splt)
{
	int	i;

	i = 0;
	while (splt && splt[i])
	{
		free (splt[i]);
		i++;
	}
	free (splt);
	return (NULL);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	w;
	int	f;

	i = 0;
	w = 0;
	f = 0;
	while (s[i])
	{
        if (s[i] == '\'' || s[i] == '"')
        {
            i += advance_quotes(&s[i]);
            w++;
			f = 1;
        }
		else if (s[i] != c && f == 0)
		{
			w++;
			f = 1;
		}
		else if (s[i] == c && f == 1)
			f = 0;
		if (s[i])
			i++;
	}
	return (w);
}

static int	ft_length(char const *s, char c)
{
	int	i;

	(void) c;
	i = 0;
    if (s[i] == '\'' || s[i] == '"')
        i += advance_quotes(&s[i]);
    if (s[i] && !ft_isspace(s[i]))
    {
	    while (s[i] && !ft_isspace(s[i]))
	    	i++;
    }
	return (i);
}

char	**ft_split_args(char const *s, char c)
{
	int		i;
	int		w;
	char	*w_len;
	char	**splt;

	if (!s)
		return (NULL);
	w = ft_wordcount(s, c);
	i = 0;
	w_len = (char *)s;
	splt = ft_calloc(w + 1, 8);
	if (splt == 0)
		return (ft_free((splt)));
	while (i < w)
	{
		while (*w_len == c)
			w_len++;
		splt[i] = ft_calloc(ft_length(w_len, c) + 1, 1);
		if (splt[i] == 0)
			return (ft_free(splt));
		ft_strlcpy(splt[i++], w_len, ft_length(w_len, c) + 1);
		w_len += ft_length(w_len, c);
    }
	return (splt);
}*/

int	args_nb(const char *command)
{
	int i;
	int	args;
	char	quote;
	int		f;

	i = 0;
	args = 0;
	quote = 0;
	f = 1;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			if (!quote)
				quote = command[i];
			else if (quote == command[i])
				quote = 0;
		}
		else if (ft_istoken(command[i]))
		{
			args++;
			while (ft_istoken(command[i]))
				i++;
			i--;
		}
		else if (!ft_isspace(command[i]) && f == 1)
		{
			args++;
			f = 0;
		}
		else if (ft_isspace(command[i]) && !quote)
			f = 1;
		i++;
	}
	return (args);
}

void	ft_cut_cmd(char *command, char **ret)
{
	int i;
	int	j;
	char	quote;
	char	*start;

	i = 0;
	j = 0;
	quote = 0;
	while (command[i])
	{
		start = &command[i];
		while (command[i] && (!ft_isspace(command[i]) || quote))
		{
			if (command[i] == '\'' || command[i] == '"')
			{
				if (!quote)
					quote = command[i];
				else if (quote == command[i])
					quote = 0;
			}
			i++;
		}
		ret[j++] = ft_strndup(start, &command[i] - start + 1);
		while (command[i] && ft_isspace(command[i]) && !ft_istoken(command[i]))
			i++;
		if (ft_istoken(command[i]))
		{
			start = &command[i];
			while (ft_istoken(command[i]))
				i++;
			ret[j++] = ft_strndup(start, &command[i] - start);
		}
	}
}

char **ft_split_args(char *command)
{
	int	i;
	char **ret;

	i = 0;
	ret = ft_calloc(args_nb(command) + 1, sizeof(char *));
	ft_cut_cmd(command, ret);
	return (ret);
}
