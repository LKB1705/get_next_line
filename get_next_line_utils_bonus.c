#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = (char) c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == ch)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*jstr;
	int		i;
	int		j;

	jstr = ft_calloc(ft_strlen(*s1) + ft_strlen(*s2) + 1, sizeof (char));
	if (!jstr)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
	{
		jstr[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		jstr[j] = s2[i];
		i++;
		j++;
	}
	jstr[j] = '\0';
	return (jstr);
}