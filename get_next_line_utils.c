/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obohbot <obohbot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 14:34:44 by obohbot           #+#    #+#             */
/*   Updated: 2026/10/27 15:30:00 by obohbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	if (!s)
		return (NULL);
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

	jstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!jstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		jstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		jstr[j++] = s2[i++];
	jstr[j] = '\0';
	return (jstr);
}
