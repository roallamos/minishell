int	word_length(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '"')
	{
		while (input[i] && input[i] != '"')
			i++;
	}
	else
	{
		while (input[i] && !ft_isspace(input[i]))
			i++;
	}
	return(i);
}

static int	nb_args(char *input)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while(input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i])
		{
			i += word_length(&input[i]);
			nb++;
		}
	}
	return (nb);
}

char	**parse(char *input)
{
	int	i;
	int	j;
	char	**args;

	i = 0;
	j = 0;
	args = (char **)malloc(sizeof(char *) * nb_args(input));
	if (!args)
		return (NULL);
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		args[j] = (char *) malloc(sizeof(char) * word_length(&input[i]) + 1);
		ft_strlcpy(args[j], &input[i], word_length(&input[i]) + 1);
		i +=  word_length(&input[i]);
		j++;
	}
	return (args);
}
