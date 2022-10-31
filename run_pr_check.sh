#!/bin/bash

NORM=`(norminette | grep Error | wc -l)`
if [ "$NORM" = 0 ] ; then
	echo "Norminette: OK"
else
	echo "Norminette: KO"
	exit 1
fi
