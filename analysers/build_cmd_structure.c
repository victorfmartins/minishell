#include "../includes/minishell.h"

// # define'<'  1
// # define'<<' 2
// # define'>'  3
// # define'>>' 4

typedef struct s_cmd
{
	char	*line
	char	*exec_cmd;
	char	*args;
	int		type; //builtin or not ou se é um comando absoluto (que começa com /)
	t_file	*infiles
	t_file	*outfiles
	void	*next;
}			t_cmd;

typedef struct s_file
{
	char	*name;
	int		type;
	void	*next;
}			t_file;

// exemplos de comandos suportados:
// echo "infile2\nsecond file" >>infile4>>infile5
// cat >>infile3<infile4>>file5
// cat <infile >>'infile3<infile4>>file5'

// essa função recebe a linha lida
// quebra essa linha entre os comandos (frases) usando a split no '|'
// essas frases estão dentro da estrutura t_cmd que esta em formato de lista
// cada nodulo dessa lista aponta para uma lista de infiles e uma de outfiles
char	**get_file_structures(t_data data)
{
	t_cmd	*frases;

	frases = ft_split_to_cmd_lst(data->line, '|'); //e se tiver || (ou)
	while (frases)
	{
		frases.outfiles = extract_out_files(&frases);
		frases.infiles = extract_in_files(&frases);
		frases = frases->next;
		i++;
	}
}

// codigo que cria a lista de outfiles (o codigo para os infiles será similar)
// a frase atual na estrutura t_cmd é alterada (limpa) para uma frase 
//sem os '>', '>>' e sem os nomes dos arquivos
// a ft_worddup foi melhorada. 
// ainda existem alterações para serem feitas tais como suporte para aspas duplas e 
//remoção das aspas dos nomes dos arquivos
t_file	*extract_out_files(t_cmd **frase)
{
	t_file	*file_lst;
	t_cmd	**frase_ptr;
	char	*new_frase_content;
	char	*word;
	int		i;
	int		j;

	frase_ptr = frase;
	new_frase_content = malloc(sizeof(char) * ft_new_frase_size(((*frase)->line), "out"));
	i = 0;
	j = 0;
	while (((*frase)->line)[i])
	{
		if (ft_strncmp(((*frase)->line) + i, ">>", 2) == 0) //word to be expanded
		{
			if (!((*frase)->line)[i + 2])
				return (ERROR);
			word = ft_worddup(((*frase)->line)[i + 2]);
			ft_fileadd_back(&file_lst, ft_filenew(word, ">>"));
			i += ft_strlen(word) + 2;
		}
		else if (((*frase)->line)[i] == '>') //word to be expanded
		{
			if (!((*frase)->line)[i + 1])
				return (ERROR);
			word = ft_worddup(((*frase)->line)[i + 1]);
			ft_fileadd_back(&file_lst, ft_filenew(word, ">"));
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

