/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:18 by vfranco-          #+#    #+#             */
/*   Updated: 2022/12/04 01:18:24 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tilde_expansion(t_data data, char **s)
{
	size_t	i;
	char	*word;
	t_env	*home;

	i = 0;
	while ((*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((i == 0 && (*s)[i] == '~') ||
			(i > 0 && ft_strchr(" =", (*s)[i - 1]) && (*s)[i] == '~'))
		{
			if ((*s)[i + 1] == '/' || (*s)[i + 1] == '\0' || (*s)[i + 1] == ':')
			{
				home = get_env_var(&data, "HOME");
				word = ft_strsubstitute(*s, "~", home->value, i);
				if (!word)
					return ;
				free(*s);
				*s = word;
				i = i + ft_strlen(home->value) - 1;
			}
		}
		i++;
	}
}

void	env_var_substitution(t_data data, char ***s, size_t *i)
{
	char	*word;
	char	*s_new;
	t_env	*env_var;

	word = ft_strcpy_until((*(*s)) + (*i), " /:");
	if (!word)
		return ;
	if (word[1])
	{
		env_var = get_env_var(&data, word + 1);
		if (!env_var)
			return (free(word));
		s_new = ft_strsubstitute((*(*s)), word, env_var->value, *i);
		free((*(*s)));
		(*(*s)) = s_new;
		if (!s_new)
			return (free(word));
		*i = *i + ft_strlen(env_var->value) - 1;
	}
	free(word);
}

void	env_var_expansion(t_data data, char **s)
{
	size_t	i;

	i = 0;
	while ((*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((*s)[i] == '$')
			env_var_substitution(data, &s, &i);
		i++;
	}
}
