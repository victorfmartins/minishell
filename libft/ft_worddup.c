/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_worddup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:21:38 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/12 09:42:10 by vfranco-         ###   ########.fr       */
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
	while (s1[n] != '\0' && !((s1[n] >= 9 && s1[n] <= 13) || s1[n] == 32))
		n++;
	s2 = malloc(sizeof(char) * n + 1);
	if (!s2)
		return (NULL);
	s2 = ft_memcpy(s2, s1, n);
	s2[n] = '\0';
	return (s2);
}

int	main()
{
	char	*str;
	char	*str_o;
	int i;

	// str_o = ft_strdup("ls -la | grep cmd_execution");
	// str_o = ft_strdup("");
	str_o = NULL;
	str = ft_worddup(str_o);
	ft_printf("%s\n", str);
	i = 0;
	// while (i < ft_strlen(str_o))
	// {
	// 	str = ft_worddup(str_o + i);
	// 	ft_printf("%s\n", str);
	// 	free(str);
	// 	i++;	
	// }
	return (i);
}
