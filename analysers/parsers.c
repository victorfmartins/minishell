/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:41:51 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/24 19:12:27 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pass_through_quotes(char *str, size_t *i, size_t *size)
{
	if (str[*i] == '\'' && ft_strchr(str + *i + 1, '\''))
	{
		if (size)
			*size += ft_strchr(str + *i + 1, '\'') - str - *i;
		*i = ft_strchr(str + *i + 1, '\'') - str;
	}
	if (str[*i] == '\"' && ft_strchr(str + *i + 1, '\"'))
	{
		if (size)
			*size += ft_strchr(str + *i + 1, '\"') - str - *i;
		*i = ft_strchr(str + *i + 1, '\"') - str;
	}
}

char	*ft_worddup(char *s1, const char *delimiters)
{
	char	*s2;
	size_t	n;

	if (!s1)
		return (NULL);
	n = 0;
	while (s1[n] && ft_strchr(delimiters, s1[n]) == 0)
	{
		pass_through_quotes(s1, &n, NULL);
		n++;
	}
	if (n == 0)
		return (NULL);
	s2 = malloc(sizeof(char) * n + 1);
	if (!s2)
		return (NULL);
	s2 = ft_memcpy(s2, s1, n);
	s2[n] = '\0';
	return (s2);
}
