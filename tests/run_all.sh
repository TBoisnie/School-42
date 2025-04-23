#!/usr/bin/env sh

echo "---------------------------------------------------------------------------------"
echo "- TEST --------------------------------------------------------------------------"
echo "---------------------------------------------------------------------------------"
echo "> Copy Symlink"
cp -P ../bins/libft_malloc.so ./libft_malloc.so

echo
echo "> NM"
nm libft_malloc.so
echo

echo "> Test 0"
gcc ./customs/test0.c
/usr/bin/time -v ./a.out
./run.sh /usr/bin/time -v ./a.out

echo "> Test 1"
gcc ./customs/test1.c
/usr/bin/time -v ./a.out
./run.sh /usr/bin/time -v ./a.out

echo "> Test 2"
gcc ./customs/test2.c
./run.sh /usr/bin/time -v ./a.out

echo "> Test 3"
gcc ./customs/test3.c
./run.sh ./a.out

echo "> Test 3 bis"
gcc ./customs/test3bis.c
./run.sh ./a.out

echo "> Test 4"
gcc -Wno-free-nonheap-object ./customs/test4.c
./run.sh ./a.out

echo "> Test 5"
gcc -Wno-unused-result ./customs/test5.c -I../incs -L. -lft_malloc
./run.sh ./a.out

echo "> Test 6"
gcc ./customs/test6.c -I../incs -L. -lft_malloc
./run.sh ./a.out
