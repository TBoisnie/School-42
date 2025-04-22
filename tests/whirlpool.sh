#!/usr/bin/env bash

# Commands
declare -lx CMD="whirlpool"

# Executable
declare -rx EXE="../bins/ft_ssl"

# Tests (Custom)
echo "--------------------------------------------------------------------------------"
echo " Test Customs (Edge cases)"
echo "--------------------------------------------------------------------------------"
echo "> echo -n \"\" | $EXE $CMD"
echo "< (stdin)= 19fa61d75522a4669b44e39c1d2e1726c530232130d407f89afee0964997f7a73e83be698b288febcf88e3e03c4f0757ea8964e59b63d93708b138cc42a66eb3"
echo -n "" | $EXE $CMD
echo
echo "> echo \"\" | $EXE $CMD"
echo "< (stdin)= 898126aab982feb2e4b99fee1e4b1cfb4208c76f35945119d24de8744016b56666dabeed478e3a9a36032bc9b8da05db7e79156dc76a7447ad0d39067745de1e"
echo "" | $EXE $CMD
echo
echo "> echo \"012345678901234567890123456789\" | $EXE $CMD"
echo "< (stdin)= 0a0cf7416b3586cba3ac195f0541c9c659cc95a0e9fde28978a697133c478e2fd42fa5a25084911bb61766b09ae72a14c0101ef36d6a6885fcf497e18913abf2"
echo "012345678901234567890123456789" | $EXE $CMD
echo
echo "> echo \"0123456789012345678901234567890\" | $EXE $CMD"
echo "< (stdin)= b443b6803fb2f279e193477cca49dfdda2ed89ef2d26323c69d51651786954f06780e7aee330ed457da86ad7f9bc22bae9c51914118dd76f7fe47bd3d2a18575"
echo "0123456789012345678901234567890" | $EXE $CMD
echo
echo "> echo \"01234567890123456789012345678901\" | $EXE $CMD"
echo "< (stdin)= bb7a6af23c74337cf7b22bd57e919f3327e7416a06510b7462031db2723fbb7a7af1eb5f28a26a802486a3691e49088e993b63c0bcf87ee93862fb3304a8defb"
echo "01234567890123456789012345678901" | $EXE $CMD
echo
echo "> echo \"012345678901234567890123456789012\" | $EXE $CMD"
echo "< (stdin)= 8a4fa1531e0439193fce810583f1f79f7fe47e3c900049ec335c997aead23ffdc006b2420bab5c6261d9cb1b901d6b2b5ff7d97fe11fea8cb471007bd999b956"
echo "012345678901234567890123456789012" | $EXE $CMD
echo
echo "> echo \"01234567890123456789012345678901234567890123456789012345678901\" | $EXE $CMD"
echo "< (stdin)= a1343c1c9ba84ba657317161ca3c24f83579d81bfa084ac8d854d40e05739cbad6804a4866dceb0870c6ee70d49b6d79d1b91443cc78b469c5a71d027be90654"
echo "01234567890123456789012345678901234567890123456789012345678901" | $EXE $CMD
echo
echo "> echo \"012345678901234567890123456789012345678901234567890123456789012\" | $EXE $CMD"
echo "< (stdin)= 07b81f834c6f0e88c28f3c2d655529eabed26f906049e4a07e4571c6eca2dcef3d10d617fc5b810565035848225e00d3a58733c14efa3720a524e666a5b9ce16"
echo "012345678901234567890123456789012345678901234567890123456789012" | $EXE $CMD
echo
echo "> echo \"0123456789012345678901234567890123456789012345678901234567890123\" | $EXE $CMD"
echo "< (stdin)= e4cc2b5fe748eb3bb77edf5d11c8a13d114bdfd36b4df3a9413594406226d1822398e722cb4edd0e79f42de25b40846683c44d93ebfac9802e36ba16dbd8a82d"
echo "0123456789012345678901234567890123456789012345678901234567890123" | $EXE $CMD
echo
echo "> echo \"01234567890123456789012345678901234567890123456789012345678901234\" | $EXE $CMD"
echo "< (stdin)= 8e1ac90c4b9bdbab9af6e09de21cb412cce859443f1545b30dc2064497d854d60dfa93500c3a6670f434777c5de978ff2d0e528f20963b5723b1174f7ca4bd63"
echo "01234567890123456789012345678901234567890123456789012345678901234" | $EXE $CMD
echo

# Tests (Subjects)
echo "--------------------------------------------------------------------------------"
echo " Test Subjects (Rendering)"
echo "--------------------------------------------------------------------------------"
echo "> echo \"42 is nice\" | $EXE $CMD"
echo "< (stdin)= f2e4e782ee1994d5210f4a4982785817b31d11762e531ded3f29dc1caef1878f14fad7cf668149993776b769d07b23e4969ebac3edbd0cd2567afaa6dd11d4ec"
echo "42 is nice" | $EXE $CMD
echo
echo "> echo \"42 is nice\" | $EXE $CMD -p"
echo "< (\"42 is nice\")= f2e4e782ee1994d5210f4a4982785817b31d11762e531ded3f29dc1caef1878f14fad7cf668149993776b769d07b23e4969ebac3edbd0cd2567afaa6dd11d4ec"
echo "42 is nice" | $EXE $CMD -p
echo
echo "> echo \"Pity the living.\" | $EXE $CMD -q -r"
echo "< c420c6f8ec9c9558a842b89625547d860f3ac277803c190bc635f0c82f1d807a252b0d936982faad9d37ef4cbc59760445fc0cd3271543c1ff3e5a7d59b31a69"
echo "Pity the living." | $EXE $CMD -q -r
echo

echo "And above all," > file

echo "> $EXE $CMD file"
echo "< ${CMD^^} (file) = 06bb68da09bfd4227a73f84335b1568e478b7cebff2ee9b8059f65dc64e30c9c6102fa296551a555bdc70acf53e3199ee8bec740ea38d3d9b51c0fe34a76cf37"
$EXE $CMD file
echo
echo "> $EXE $CMD -r file"
echo "< 06bb68da09bfd4227a73f84335b1568e478b7cebff2ee9b8059f65dc64e30c9c6102fa296551a555bdc70acf53e3199ee8bec740ea38d3d9b51c0fe34a76cf37 file"
$EXE $CMD -r file
echo
echo "> $EXE $CMD -s \"pity those that aren't following baerista on spotify\""
echo "< ${CMD^^} (\"pity those that aren't following baerista on spotify.\") = 91a193af00f4d5b4b606b885fb38bf9ef0df821e14a7e66c03a542470ca0328897a19d2f168882695170886036d534296ecf408a92481d18eb0f8969f64af265"
$EXE $CMD -s "pity those that aren't following baerista on spotify."
echo
echo "> echo \"be sure to handle edge cases carefully\" | $EXE $CMD -p file"
echo "< (\"be sure to handle edge cases carefully\")= c0a77cfb2f85c1734abb3ca2163d08840b5a55375e2de767398a5ab6d53350fd6498fbbc22de7a42cc3e385fab4c3685358adaf9f355d4191e78ce9aded65028"
echo "< ${CMD^^} (file) = 06bb68da09bfd4227a73f84335b1568e478b7cebff2ee9b8059f65dc64e30c9c6102fa296551a555bdc70acf53e3199ee8bec740ea38d3d9b51c0fe34a76cf37"
echo "be sure to handle edge cases carefully" | $EXE $CMD -p file
echo
echo "> echo \"some of this will not make sense at first\" | $EXE $CMD file"
echo "< ${CMD^^} (file) = 06bb68da09bfd4227a73f84335b1568e478b7cebff2ee9b8059f65dc64e30c9c6102fa296551a555bdc70acf53e3199ee8bec740ea38d3d9b51c0fe34a76cf37"
echo "some of this will not make sense at first" | $EXE $CMD file
echo
echo "> echo \"but eventually you will understand\" | $EXE $CMD -p -r file"
echo "< (\"but eventually you will understand\")= f9d4cf133e39790809877c3967d16e32f4487640cae49ee3d63e7f88db218aafa176ca9a40ef3e0cb8aeb783f89ff1abaa89853e650508e2c859992605eed498"
echo "< 06bb68da09bfd4227a73f84335b1568e478b7cebff2ee9b8059f65dc64e30c9c6102fa296551a555bdc70acf53e3199ee8bec740ea38d3d9b51c0fe34a76cf37 file"
echo "but eventually you will understand" | $EXE $CMD -p -r file
echo
echo "> echo \"GL HF let's go\" | $EXE $CMD -p -s \"foo\" file"
echo "< (\"GL HF let's go\")= f52b03b6d5143706db93c31bbb8fa1cbfc21ab6456a27f8bd9ee1a45e83fbcd4e69f4dcfa3b62b5324060aab4238147a227366d170426662a6b31e7fff2ab4af"
echo "< ${CMD^^} (\"foo\") = b1b2ee48991281a439da2b8b406d579a9b9878d94bd1de813de8124a1df79d9dd603c728068aff13d724ef55e0a24313a7b84b0bf638682facb5f71fef96701f"
echo "< ${CMD^^} (file) = 06bb68da09bfd4227a73f84335b1568e478b7cebff2ee9b8059f65dc64e30c9c6102fa296551a555bdc70acf53e3199ee8bec740ea38d3d9b51c0fe34a76cf37"
echo "GL HF let's go" | $EXE $CMD -p -s "foo" file
echo
echo "> echo \"one more thing\" | $EXE $CMD -r -p -s \"foo\" file -s \"bar\""
echo "< (\"one more thing\")= 17380ec486cc73ebeb9ca197462ba7877a2564b9f2a67f4feca92d99a563c33e18bdd08e67f913c650e1eae867fbc9ffc1d26090b59a70a4ab47a32b677bd6f0"
echo "< b1b2ee48991281a439da2b8b406d579a9b9878d94bd1de813de8124a1df79d9dd603c728068aff13d724ef55e0a24313a7b84b0bf638682facb5f71fef96701f \"foo\""
echo "< 06bb68da09bfd4227a73f84335b1568e478b7cebff2ee9b8059f65dc64e30c9c6102fa296551a555bdc70acf53e3199ee8bec740ea38d3d9b51c0fe34a76cf37 file"
echo "< ft_ssl: $CMD: -s: No such file or directory"
echo "< ft_ssl: $CMD: bar: No such file or directory"
echo "one more thing" | $EXE $CMD -r -p -s "foo" file -s "bar"
echo
echo "> echo \"just to be extra clear\" | $EXE $CMD -r -q -p -s \"foo\" file"
echo "< just to be extra clear"
echo "< 673c0f8fb75ab53d0f843fa03f57326ee833c75c10fcf15e8e07e5e395a07646f34e9744bbd1d05fb2d7c2b9ba271104a2d89b8af83fb22921ceaa9f2e4e03fc"
echo "< b1b2ee48991281a439da2b8b406d579a9b9878d94bd1de813de8124a1df79d9dd603c728068aff13d724ef55e0a24313a7b84b0bf638682facb5f71fef96701f"
echo "< 06bb68da09bfd4227a73f84335b1568e478b7cebff2ee9b8059f65dc64e30c9c6102fa296551a555bdc70acf53e3199ee8bec740ea38d3d9b51c0fe34a76cf37"
echo "just to be extra clear" | $EXE $CMD -r -q -p -s "foo" file
