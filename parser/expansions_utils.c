/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/22 16:09:54 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strsubstitute(char *str, char *del, char *insert, int pos)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(insert) + 1));
	if (!new_str)
		return (NULL);
	while (str[i] && i < pos)
	{
		new_str[i] = str[i];
		i++;
	}
	while (insert[j])
		new_str[i++] = insert[j++];
	while (str[i - ft_strlen(insert) + ft_strlen(del)])
	{
		new_str[i] = str[i - ft_strlen(insert) + ft_strlen(del)];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strcpy_until(char *str, char *delimiter)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	while (str[i] && !ft_strchr(delimiter, str[i]))
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}
