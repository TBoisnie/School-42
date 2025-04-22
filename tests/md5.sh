#!/usr/bin/env bash

#
# https://emn178.github.io/online-tools/md5.html
#

# Commands
declare -lx CMD="md5"

# Executable
declare -rx EXE="../bins/ft_ssl"

# Tests (Custom)
echo "--------------------------------------------------------------------------------"
echo " Test Customs (Edge cases)"
echo "--------------------------------------------------------------------------------"
echo "> echo -n \"\" | $EXE $CMD"
echo "< (stdin)= d41d8cd98f00b204e9800998ecf8427e"
echo -n "" | $EXE $CMD
echo
echo "> echo \"\" | $EXE $CMD"
echo "< (stdin)= 68b329da9893e34099c7d8ad5cb9c940"
echo "" | $EXE $CMD
echo
echo "> echo \"0123456789012345678901234567890123456789012345678901234\" | $EXE $CMD"
echo "< (stdin)= be575078a6562d871eee08153baf46c2"
echo "0123456789012345678901234567890123456789012345678901234" | $EXE $CMD
echo
echo "> echo \"01234567890123456789012345678901234567890123456789012345\" | $EXE $CMD"
echo "< (stdin)= ea4b6a3305b744d1c4be59ae1880145b"
echo "01234567890123456789012345678901234567890123456789012345" | $EXE $CMD
echo
echo "> echo \"012345678901234567890123456789012345678901234567890123456\" | $EXE $CMD"
echo "< (stdin)= 5f3bebb73ee90e3c8a726f5f9a147b38"
echo "012345678901234567890123456789012345678901234567890123456" | $EXE $CMD
echo
echo "> echo \"012345678901234567890123456789012345678901234567890123456789012\" | $EXE $CMD"
echo "< (stdin)= 5c74cd961c47c959e575d46f7276dccd"
echo "012345678901234567890123456789012345678901234567890123456789012" | $EXE $CMD
echo
echo "> echo \"0123456789012345678901234567890123456789012345678901234567890123\" | $EXE $CMD"
echo "< (stdin)= 5267c61d6bac1e00ed5e45235387b1ad"
echo "0123456789012345678901234567890123456789012345678901234567890123" | $EXE $CMD
echo
echo "> echo \"01234567890123456789012345678901234567890123456789012345678901234\" | $EXE $CMD"
echo "< (stdin)= 8019346c9af35e274e94949b70addf99"
echo "01234567890123456789012345678901234567890123456789012345678901234" | $EXE $CMD
echo

# Tests (Subjects)
echo "--------------------------------------------------------------------------------"
echo " Test Subjects (Rendering)"
echo "--------------------------------------------------------------------------------"
echo "> echo \"42 is nice\" | $EXE $CMD"
echo "< (stdin)= 35f1d6de0302e2086a4e472266efb3a9"
echo "42 is nice" | $EXE $CMD
echo
echo "> echo \"42 is nice\" | $EXE $CMD -p"
echo "< (\"42 is nice\")= 35f1d6de0302e2086a4e472266efb3a9"
echo "42 is nice" | $EXE $CMD -p
echo
echo "> echo \"Pity the living.\" | $EXE $CMD -q -r"
echo "< e20c3b973f63482a778f3fd1869b7f25"
echo "Pity the living." | $EXE $CMD -q -r
echo

echo "And above all," > file

echo "> $EXE $CMD file"
echo "< ${CMD^^} (file) = 53d53ea94217b259c11a5a2d104ec58a"
$EXE $CMD file
echo
echo "> $EXE $CMD -r file"
echo "< 53d53ea94217b259c11a5a2d104ec58a file"
$EXE $CMD -r file
echo
echo "> $EXE $CMD -s \"pity those that aren't following baerista on spotify\""
echo "< ${CMD^^} (\"pity those that aren't following baerista on spotify.\") = a3c990a1964705d9bf0e602f44572f5f"
$EXE $CMD -s "pity those that aren't following baerista on spotify."
echo
echo "> echo \"be sure to handle edge cases carefully\" | $EXE $CMD -p file"
echo "< (\"be sure to handle edge cases carefully\")= 3553dc7dc5963b583c056d1b9fa3349c"
echo "< ${CMD^^} (file) = 53d53ea94217b259c11a5a2d104ec58a"
echo "be sure to handle edge cases carefully" | $EXE $CMD -p file
echo
echo "> echo \"some of this will not make sense at first\" | $EXE $CMD file"
echo "< ${CMD^^} (file) = 53d53ea94217b259c11a5a2d104ec58a"
echo "some of this will not make sense at first" | $EXE $CMD file
echo
echo "> echo \"but eventually you will understand\" | $EXE $CMD -p -r file"
echo "< (\"but eventually you will understand\")= dcdd84e0f635694d2a943fa8d3905281"
echo "< 53d53ea94217b259c11a5a2d104ec58a file"
echo "but eventually you will understand" | $EXE $CMD -p -r file
echo
echo "> echo \"GL HF let's go\" | $EXE $CMD -p -s \"foo\" file"
echo "< (\"GL HF let's go\")= d1e3cc342b6da09480b27ec57ff243e2"
echo "< ${CMD^^} (\"foo\") = acbd18db4cc2f85cedef654fccc4a4d8"
echo "< ${CMD^^} (file) = 53d53ea94217b259c11a5a2d104ec58a"
echo "GL HF let's go" | $EXE $CMD -p -s "foo" file
echo
echo "> echo \"one more thing\" | $EXE $CMD -r -p -s \"foo\" file -s \"bar\""
echo "< (\"one more thing\")= a0bd1876c6f011dd50fae52827f445f5"
echo "< acbd18db4cc2f85cedef654fccc4a4d8 \"foo\""
echo "< 53d53ea94217b259c11a5a2d104ec58a file"
echo "< ft_ssl: $CMD: -s: No such file or directory"
echo "< ft_ssl: $CMD: bar: No such file or directory"
echo "one more thing" | $EXE $CMD -r -p -s "foo" file -s "bar"
echo
echo "> echo \"just to be extra clear\" | $EXE $CMD -r -q -p -s \"foo\" file"
echo "< just to be extra clear"
echo "< 3ba35f1ea0d170cb3b9a752e3360286c"
echo "< acbd18db4cc2f85cedef654fccc4a4d8"
echo "< 53d53ea94217b259c11a5a2d104ec58a"
echo "just to be extra clear" | $EXE $CMD -r -q -p -s "foo" file
