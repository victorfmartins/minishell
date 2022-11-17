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
