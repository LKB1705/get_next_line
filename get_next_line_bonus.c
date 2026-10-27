/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line_bonus.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: obohbot <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/10/27 15:16:35 by obohbot        #+#    #+#                */
/*   Updated: 2026/10/27 15:31:15 by obohbot        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

char	*copyf(char *stash)
{
	int		i;
	char	*str;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	str = (char *)malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*clear_stash(char *stash)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	str = (char *)malloc(ft_strlen(stash) - i + 1);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		str[j++] = stash[i++];
	str[j] = '\0';
	free(stash);
	return (str);
}

char	*readf(int fd, char *stash)
{
	char			*buffer;
	ssize_t			lu;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	lu = 1;
	while (!ft_strchr(stash, '\n') && lu > 0)
	{
		lu = read(fd, buffer, BUFFER_SIZE);
		if (lu == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[lu] = '\0';
		stash = ft_strjoin(stash, buffer);
		free(stash);
		if (!stash)
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	stash[FD_MAX];
	char		*to_print;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = readf(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	to_print = copyf(stash[fd]);
	stash[fd] = clear_stash(stash[fd]);
	return (to_print);
}
