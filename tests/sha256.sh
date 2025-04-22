#!/usr/bin/env bash

#
# https://emn178.github.io/online-tools/sha256.html
#

# Commands
declare -lx CMD="sha256"

# Executable
declare -rx EXE="../bins/ft_ssl"

# Tests (Custom)
echo "--------------------------------------------------------------------------------"
echo " Test Customs (Edge cases)"
echo "--------------------------------------------------------------------------------"
echo "> echo -n \"\" | $EXE $CMD"
echo "< (stdin)= e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
echo -n "" | $EXE $CMD
echo
echo "> echo \"\" | $EXE $CMD"
echo "< (stdin)= 01ba4719c80b6fe911b091a7c05124b64eeece964e09c058ef8f9805daca546b"
echo "" | $EXE $CMD
echo
echo "> echo \"0123456789012345678901234567890123456789012345678901234\" | $EXE $CMD"
echo "< (stdin)= 695f51256e9c00cb6bcfecf9e68b72773dbaf2f23fd9903d175d501bafa8c14c"
echo "0123456789012345678901234567890123456789012345678901234" | $EXE $CMD
echo
echo "> echo \"01234567890123456789012345678901234567890123456789012345\" | $EXE $CMD"
echo "< (stdin)= bba401637af6d8d9ae2ecf690476734e1b313c1bbe7e4fa159e1d229084667ba"
echo "01234567890123456789012345678901234567890123456789012345" | $EXE $CMD
echo
echo "> echo \"012345678901234567890123456789012345678901234567890123456\" | $EXE $CMD"
echo "< (stdin)= b1538291f803af2774badf5bfdb6c2b85a92bab817c55741e1aa16a1bbc1821e"
echo "012345678901234567890123456789012345678901234567890123456" | $EXE $CMD
echo
echo "> echo \"012345678901234567890123456789012345678901234567890123456789012\" | $EXE $CMD"
echo "< (stdin)= 7e7bcb3f889bb9fb4153bf9ce6b3047cdf57081a5c38ca036845afddae780e14"
echo "012345678901234567890123456789012345678901234567890123456789012" | $EXE $CMD
echo
echo "> echo \"0123456789012345678901234567890123456789012345678901234567890123\" | $EXE $CMD"
echo "< (stdin)= 34bbbcb752524c2f570348028fb7a2b744ae52e280fb32aea607b910fc9a57f5"
echo "0123456789012345678901234567890123456789012345678901234567890123" | $EXE $CMD
echo
echo "> echo \"01234567890123456789012345678901234567890123456789012345678901234\" | $EXE $CMD"
echo "< (stdin)= 041781ffa2816c7c4046975fdc47f90ada413481c83e37a9a5bdea6022047f8e"
echo "01234567890123456789012345678901234567890123456789012345678901234" | $EXE $CMD
echo

# Tests (Subjects)
echo "--------------------------------------------------------------------------------"
echo " Test Subjects (Rendering)"
echo "--------------------------------------------------------------------------------"
echo "> echo \"42 is nice\" | $EXE $CMD"
echo "< (stdin)= a5482539287a4069ebd3eb45a13a47b1968316c442a7e69bc6b9c100b101d65d"
echo "42 is nice" | $EXE $CMD
echo
echo "> echo \"42 is nice\" | $EXE $CMD -p"
echo "< (\"42 is nice\")= a5482539287a4069ebd3eb45a13a47b1968316c442a7e69bc6b9c100b101d65d"
echo "42 is nice" | $EXE $CMD -p
echo
echo "> echo \"Pity the living.\" | $EXE $CMD -q -r"
echo "< 40133cfe543247c1cae0ffb0003c1179ce9fb0046bee19f9fca167380643ba45"
echo "Pity the living." | $EXE $CMD -q -r
echo

echo "And above all," > file

echo "> $EXE $CMD file"
echo "< ${CMD^^} (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705"
$EXE $CMD file
echo
echo "> $EXE $CMD -r file"
echo "< f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file"
$EXE $CMD -r file
echo
echo "> $EXE $CMD -s \"pity those that aren't following baerista on spotify\""
echo "< ${CMD^^} (\"pity those that aren't following baerista on spotify.\") = 7838c25c9debff86c584245d67b429186d3850c89da31c0b49b8d0380a3e14bf"
$EXE $CMD -s "pity those that aren't following baerista on spotify."
echo
echo "> echo \"be sure to handle edge cases carefully\" | $EXE $CMD -p file"
echo "< (\"be sure to handle edge cases carefully\")= ef9241f878a1da676104a81239792a2817bc0390a427ca20bad1a59030fd20c2"
echo "< ${CMD^^} (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705"
echo "be sure to handle edge cases carefully" | $EXE $CMD -p file
echo
echo "> echo \"some of this will not make sense at first\" | $EXE $CMD file"
echo "< ${CMD^^} (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705"
echo "some of this will not make sense at first" | $EXE $CMD file
echo
echo "> echo \"but eventually you will understand\" | $EXE $CMD -p -r file"
echo "< (\"but eventually you will understand\")= 43da940057fd3b7453ee91b3a056a41343e6f0bce315570ed27e06c993a539da"
echo "< f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file"
echo "but eventually you will understand" | $EXE $CMD -p -r file
echo
echo "> echo \"GL HF let's go\" | $EXE $CMD -p -s \"foo\" file"
echo "< (\"GL HF let's go\")= f33201f3d70c9dccccec022e2ff0df2006e016f153f600407917d14955fbec22"
echo "< ${CMD^^} (\"foo\") = 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae"
echo "< ${CMD^^} (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705"
echo "GL HF let's go" | $EXE $CMD -p -s "foo" file
echo
echo "> echo \"one more thing\" | $EXE $CMD -r -p -s \"foo\" file -s \"bar\""
echo "< (\"one more thing\")= 720bbf63077e0bea3b70c87954123daa6fcf32f973f4d646622bd016b140ec75"
echo "< 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae \"foo\""
echo "< f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file"
echo "< ft_ssl: $CMD: -s: No such file or directory"
echo "< ft_ssl: $CMD: bar: No such file or directory"
echo "one more thing" | $EXE $CMD -r -p -s "foo" file -s "bar"
echo
echo "> echo \"just to be extra clear\" | $EXE $CMD -r -q -p -s \"foo\" file"
echo "< just to be extra clear"
echo "< 41c3da28172faf72bb777d6a428b6d801427d02513c56cd9e3672f44383f8eee"
echo "< 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae"
echo "< f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705"
echo "just to be extra clear" | $EXE $CMD -r -q -p -s "foo" file
