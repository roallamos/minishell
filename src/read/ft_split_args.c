
#include <minishell.h>

static int  advance_quotes(const char *s)
{
    char quote;
    int i;

    i = 0;
    quote = s[i++];
    while (s[i] && s[i] != quote)
        i++;
    if (s[i])
        i++;
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
        }
		else if (s[i] != c && f == 0)
		{
			w++;
			f = 1;
		}
		else if (s[i] == c && f == 1)
			f = 0;
		i++;
	}
	return (w);
}

static int	ft_length(char const *s, char c)
{
	int	i;

	i = 0;
    if (s[i] == '\'' || s[i] == '"')
        i += advance_quotes(&s[i]);
    else
    {
	    while (s[i] != c && s[i])
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
}
