/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:43:30 by asoler            #+#    #+#             */
/*   Updated: 2022/11/23 08:14:14 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define ENVIROMENT_H

# define TABLE_SIZE 5382

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

unsigned int	hash(char *name);
void			print_table(t_env *hash_table[TABLE_SIZE]);
t_env			*ft_envnew(char	*key, char *value);
void			ft_env_addback(t_env **lst, t_env *new);
void			ft_envdelone(t_env *env, void (*del)(void*));
void			ft_envclear(t_env **env, void (*del)(void *));
void			print_env_lst(t_env *env);
void			free_lst(t_env *env);
int				free_and_count_array(char **array, void (*f)(void *));

#endif
