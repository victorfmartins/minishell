/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_worddup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:21:38 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/23 18:08:13 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_worddup(const char *s1)
{
	char	*s2;
	size_t	n;

	if (!s1)
		return (NULL);
	n = 0;
	while (s1[n] != '\0' && !ft_isspace(s1[n]) && !ft_isredirect(s1[n]))
	{
		if (s1[n] == '\'' && ft_strchr(s1 + n + 1, '\''))
			n = ft_strchr(s1 + n + 1, '\'') - s1;
		n++;
	}
	s2 = malloc(sizeof(char) * n + 1);
	if (!s2)
		return (NULL);
	s2 = ft_memcpy(s2, s1, n);
	s2[n] = '\0';
	return (s2);
}
