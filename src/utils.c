/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:15:02 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/16 17:15:54 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"
/*
int		ft_atoi(char *s)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		res = res * 10 + *s - 48;
		s++;
	}
	return (res * sign);
}
*/
unsigned long	ft_atoill(char *s)
{
	unsigned long	res;

	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+')
		s++;
	s += 2;
	while (*s)
	{
		if (*s >= 'A' && *s <= 'F')
			res = res * 16 + *s - 55;
		else
			res = res * 16 + *s - 48;
		s++;
	}
	return (res);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
	char            *s2;
	unsigned long   j;

	if (!s)
		return (0);
	j = 0;
	if (start > ft_strlen(s))
	{
		s2 = malloc(sizeof(char));
		s2[0] = '\0';
		return (s2);
	}
	if (ft_strlen(s) - start < len)
		s2 = malloc(sizeof(char) * ft_strlen(s) - start + 1);
	else
		s2 = malloc(len + 1);
	if (!s2)
		return (0);
	while (j < len && s[start + j] != '\0')
	{
		s2[j] = s[start + j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

static int	words2(const char *s, char c)
{
	int	j;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
			{
				s++;
			}
			j++;
		}
		else
			++s;
	}	
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		size;
	int		j;
	char	**res;

	i = 0;
	size = 0;
	j = 0;
	res = (char **) malloc((words2(s, c) * (sizeof(char *))) + 8);
	if (!res || !s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			size = 0;
			while (*s && *s != c && ++size)
				s++;
			res[j++] = ft_substr(s - size, 0, size);
		}
		else
			++s;
	}
	res[j] = NULL;
	return (res);
}
