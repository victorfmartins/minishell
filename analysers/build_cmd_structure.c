/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:37:21 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/15 11:15:57 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define ERROR 0
#define DIR 1
#define HERE_DIR 2
#define REDIR 3
#define O_REDIR 4

t_file	*ft_filenew(void *name, int type)
{
	t_file	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->name = name;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}

void	ft_fileadd_back(t_file **lst, t_file *new)
{
	t_file	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

t_cmd	*ft_cmdnew(void *line)
{
	t_cmd	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->line = line;
	lst->next = NULL;
	return (lst);
}

void	ft_cmd_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

t_cmd	*ft_split_to_cmd_lst(char *line, char delimiter)
{
	char	**frases;
	t_cmd	*lst;
	int		i;

	frases = ft_split(line, delimiter);
	i = 0;
	while (frases[i])
	{
		ft_cmd_addback(&lst, ft_cmdnew(line));
		i++;
	}
	return (lst);
}

size_t	ft_new_frase_size(char *str, int mode)
{
	size_t	size;
	size_t	i;

	if (!str)
		return (ERROR);
	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '>' * (mode == REDIR) + '<' * (mode == DIR))
			while (str[i] && !ft_isspace(str[i])
				&& str[i] == '<' * (mode == REDIR) + '>' * (mode == DIR))
			{
				if (str[i] == '\'' && ft_strchr(str + i + 1, '\''))
					i = ft_strchr(str + i + 1, '\'') - str;
				i++;
			}
		i++;
		size++;
	}
	return (size);
}

/*
	codigo que cria a lista de outfiles (o codigo para os infiles será similar)
	a frase atual na estrutura t_cmd é alterada (limpa) para uma frase 
	sem os '>', '>>' e sem os nomes dos arquivos
	a ft_worddup foi melhorada. 
	ainda existem alterações para serem feitas tais como suporte para aspas duplas e 
	remoção das aspas dos nomes dos arquivos
*/
t_file	*extract_out_files(t_cmd **frase)
{
	t_file	*file_lst;
	t_cmd	**frase_ptr;
	char	*new_frase_content;
	char	*word;
	int		i;
	int		j;

	frase_ptr = frase;
	new_frase_content = malloc(sizeof(char) * ft_new_frase_size(((*frase)->line), REDIR));
	i = 0;
	j = 0;
	while (((*frase)->line)[i])
	{
		if (ft_strncmp(((*frase)->line) + i, ">>", 2) == 0)
		{
			if (!((*frase)->line)[i + 2])
				return (ERROR);
			word = ft_worddup(((*frase)->line) + i + 2);
			ft_fileadd_back(&file_lst, ft_filenew(word, O_REDIR));
			i += ft_strlen(word) + 2;
		}
		else if (((*frase)->line)[i] == '>')
		{
			if (!((*frase)->line)[i + 1])
				return (ERROR);
			word = ft_worddup(((*frase)->line) + i + 1);
			ft_fileadd_back(&file_lst, ft_filenew(word, REDIR));
			i += ft_strlen(word) + 1;
		}
		if (((*frase)->line)[i])
			new_frase_content[j] = ((*frase)->line)[i];
		i++;
		j++;
	}
	free((*frase)->line);
	(*frase)->line = new_frase_content;
	return (file_lst);
}

/*
	exemplos de comandos suportados:
	echo "infile2\nsecond file" >>infile4>>infile5
	cat >>infile3<infile4>>file5
	cat <infile >>'infile3<infile4>>file5'
	ls <<infile>>outfile2
	cat <infile2<<infile>>outfile2

	essa função recebe a linha lida
	quebra essa linha entre os comandos (frases) usando a split no '|'
	essas frases estão dentro da estrutura t_cmd que esta em formato de lista
	cada nodulo dessa lista aponta para uma lista de infiles e uma de outfiles
*/
t_cmd	*get_file_structures(t_data *data)
{
	t_cmd	*frases;

	frases = ft_split_to_cmd_lst(data->line, '|'); //e se tiver || (ou)
	while (frases)
	{
		frases->outfiles = extract_out_files(&frases);
		// frases->infiles = extract_in_files(&frases);
		frases = frases->next;
	}
	return (frases);
}

void	print_file_lst(t_file *lst)
{
	while (lst)
	{
		ft_printf("file:%s\ttype%i\n", (char *)lst->name, lst->type);
		lst = lst->next;
	}
}

void	print_cmd_lst(t_cmd *lst)
{
	while (lst)
	{
		ft_printf("%s\n", (char *)lst->line);
		print_file_lst(lst->outfiles);
		// print_file_lst(lst->infiles);
		lst = lst->next;
	}
}
