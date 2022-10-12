#!/bin/bash
make
echo "I'm the infile file" > infile

>outfile; >outfile2; diff outfile outfile2

echo "       -----test1-----"
./pipex infile "ls -l" "wc -l" outfile
       < infile ls -l | wc -l > outfile2
diff outfile outfile2

echo "       -----test2-----"
./pipex infile "cat /etc/passwd" "grep -v '#'" "wc -l" outfile
       < infile cat /etc/passwd | grep -v "#" | wc -l > outfile2
diff outfile outfile2

echo "       -----test3-----"
./pipex infile "cat" "grep name" "grep -E a$" "wc -l" outfile
         cat infile | grep name | grep -E a$ | wc -l > outfile2
diff outfile outfile2

echo "       -----test4-----"
./pipex infile "cat" "grep -i a" "grep -E e$" outfile
         cat infile | grep -i a | grep -E e$ > outfile2 
diff outfile outfile2

echo "       -----test5-----"
./pipex infile "cat" "grep -v a" "grep -E s$" outfile
         cat infile | grep -v a | grep -E s$ > outfile2
diff outfile outfile2

echo "       -----test6-----"
./pipex infile "cat" "grep -i s" "sort" "head -n 3" "uniq" "tail -5" "wc -l" outfile
         cat infile | grep -i s | sort | head -n 3 | uniq | tail -5 | wc -l > outfile2 
diff outfile outfile2

echo "       -----test7-----"
./pipex infile "cat" "grep -i s" "head -n 3" "sort" "uniq" "tail -5" outfile
         cat infile | grep -i s | head -n 3 | sort | uniq | tail -5 > outfile2
diff outfile outfile2
