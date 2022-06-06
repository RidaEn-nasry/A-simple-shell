/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:30:13 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/03 09:33:33 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i = i + 1;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	size_t	k;
	char	*nstr;

	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	i = 0;
	k = 0;
	nstr = (char *)malloc(s1len + s2len + 1);
	if (!nstr)
		return (NULL);
	while (s1[k])
		nstr[i++] = s1[k++];
	k = 0;
	while (s2[k])
		nstr[i++] = s2[k++];
	nstr[i] = '\0';
	return (nstr);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!p)
		return (0);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	i = 0;
	if (s == 0)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
	{
		p = (char *)malloc(sizeof(char ) * 1);
		*p = '\0';
		return (p);
	}
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (s[start + i] && i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (p[i])
	{
		if (p[i] == (char)c)
			return (&p[i]);
		i++;
	}
	if (p[i] == (char)c)
		return (&p[i]);
	return (0);
}
