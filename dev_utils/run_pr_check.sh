#!/bin/bash

GREEN="\033[1;32m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
RED="\033[1;31m"
RESET="\033[0m"

NORM=`(norminette | grep Error | wc -l)`
error=$(norminette | grep Error)
if [ "$NORM" = 0 ] ; then
	echo -e "$CYAN Norminette:$RESET$GREEN OK$RESET"
else
	echo -e "$CYAN Norminette:$RESET$RED KO$RESET"
	echo -e "$YELLOW$error$RESET"
	exit 1
fi

make
echo "I'm the infile file" > infile

rm output_minishell output_shell
>output_minishell; >output_shell; diff output_minishell output_shell

< infile ls -l | wc -l >> output_shell
< infile cat /etc/passwd | grep -v "#" | wc -l >> output_shell
< infile cat | grep name | grep -E a$ | wc -l >> output_shell
< infile cat | grep -i a | grep -E e$ >> output_shell
< infile cat | grep -v a | grep -E s$ >> output_shell
< infile cat | grep -i s | sort | head -n 3 | uniq | tail -5 | wc -l >> output_shell
< infile cat | grep -i s | head -n 3 | sort | uniq | tail -5 >> output_shell

./minishell <<EOF
< infile ls -l | wc -l >> output_minishell
< infile cat /etc/passwd | grep -v "#" | wc -l >> output_minishell
< infile cat | grep name | grep -E a$ | wc -l >> output_minishell
< infile cat | grep -i a | grep -E e$ >> output_minishell
< infile cat | grep -v a | grep -E s$ >> output_minishell
< infile cat | grep -i s | sort | head -n 3 | uniq | tail -5 | wc -l >> output_minishell
< infile cat | grep -i s | head -n 3 | sort | uniq | tail -5 >> output_minishell
exit
EOF

COMPARE=`(diff output_minishell output_shell | wc -c)`
error=$(diff output_minishell output_shell)

rm output_minishell output_shell infile
make fclean_all

if [ "$COMPARE" = 0 ] ; then
	echo -e "$CYAN Test:$RESET$GREEN OK$RESET"
else
	echo -e "$CYAN Norminette:$RESET$RED KO$RESET"
	echo -e "$YELLOW$error$RESET"
	exit 1
fi