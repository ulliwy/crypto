rm -rf sha256_test_results
mkdir sha256_test_results
cat orig > bigtest
YEL='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo
echo "--------------------"
echo "SHA256 test results:"
echo "--------------------"
# sha256

# 1
echo "pickle rick" | ../ft_ssl sha256 > sha256_test_results/sha256_1_1
echo "pickle rick" | openssl sha -sha256 > sha256_test_results/sha256_1_2

printf "1. echo: "
if `diff sha256_test_results/sha256_1_1 sha256_test_results/sha256_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 2
cat bigtest | ../ft_ssl sha256 > sha256_test_results/sha256_1_1_1
cat bigtest | openssl sha -sha256 > sha256_test_results/sha256_1_2_1

printf "2. echo bigtest: "
if `diff sha256_test_results/sha256_1_1 sha256_test_results/sha256_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 3
echo "Do not pity the dead, Harry." | ../ft_ssl sha256 -p > sha256_test_results/sha256_2_1
printf "Do not pity the dead, Harry.\n7197000d32ca5a13cf923ba196286a72daa06e9f168c4dd5753f917568ea373f\n" > sha256_test_results/sha256_2_2

printf "3. echo, flags: -p: "
if `diff sha256_test_results/sha256_2_1 sha256_test_results/sha256_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 4
echo "Pity the living." | ../ft_ssl sha256 -q -r > sha256_test_results/sha256_3_1
echo "Pity the living." | openssl sha256 > sha256_test_results/sha256_3_2

printf "4. echo, flags: -p -r: "
if `diff sha256_test_results/sha256_3_1 sha256_test_results/sha256_3_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 5
echo "And above all," > file
../ft_ssl sha256 file > sha256_test_results/sha256_4_1
# openssl sha256 file > sha256_test_results/sha256_4_2
echo "SHA256 (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705" > sha256_test_results/sha256_4_2

printf "5. file: "
if `diff sha256_test_results/sha256_4_1 sha256_test_results/sha256_4_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 6
../ft_ssl sha256 -r file > sha256_test_results/sha256_5_1
#openssl sha256 file > sha256_test_results/sha256_5_2
echo "f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file" > sha256_test_results/sha256_5_2

printf "6. file, flags: -r: "
if `diff sha256_test_results/sha256_5_1 sha256_test_results/sha256_5_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 7
../ft_ssl sha256 -s "pity those that aren't following baerista on spotify." > sha256_test_results/sha256_6_1
#echo "pity those that aren't following baerista on spotify." | openssl sha256 > sha256_test_results/sha256_6_2
printf "SHA256 (\"pity those that aren't following baerista on spotify.\") = 7838c25c9debff86c584245d67b429186d3850c89da31c0b49b8d0380a3e14bf\n" > sha256_test_results/sha256_6_2

printf "7. flags: -s: "
if `diff sha256_test_results/sha256_6_1 sha256_test_results/sha256_6_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 8
echo "be sure to handle edge cases carefully" | ../ft_ssl sha256 -p file > sha256_test_results/sha256_7_1
#echo "be sure to handle edge cases carefully" | openssl sha256 file > sha256_test_results/sha256_7_2
printf "be sure to handle edge cases carefully\nef9241f878a1da676104a81239792a2817bc0390a427ca20bad1a59030fd20c2\nSHA256 (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705\n" > sha256_test_results/sha256_7_2

printf "8. echo, flags: -p, file: "
if `diff sha256_test_results/sha256_7_1 sha256_test_results/sha256_7_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 9
echo "some of this will not make sense at first" | ../ft_ssl sha256 file > sha256_test_results/sha256_8_1
#echo "some of this will not make sense at first" | sha256 file > sha256_test_results/sha256_8_2
printf "SHA256 (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705\n" > sha256_test_results/sha256_8_2

printf "9. echo, file: "
if `diff sha256_test_results/sha256_8_1 sha256_test_results/sha256_8_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 10
echo "but eventually you will understand" | ../ft_ssl sha256 -p -r file > sha256_test_results/sha256_9_1
# echo "but eventually you will understand" | openssl sha256> sha256_test_results/sha256_9_2
printf "but eventually you will understand\n43da940057fd3b7453ee91b3a056a41343e6f0bce315570ed27e06c993a539da\nf9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file\n" > sha256_test_results/sha256_9_2

printf "10. echo, flags: -p -r, file: "
if `diff sha256_test_results/sha256_9_1 sha256_test_results/sha256_9_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 11
echo "GL HF let's go" | ../ft_ssl sha256 -p -s "foo" file > sha256_test_results/sha256_10_1
#echo "GL HF let's go" | openssl sha256 -p -s "foo" file > sha256_test_results/sha256_10_2

printf "GL HF let\'s go\nf33201f3d70c9dccccec022e2ff0df2006e016f153f600407917d14955fbec22\nSHA256 (\"foo\") = 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae\nSHA256 (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705\n" > sha256_test_results/sha256_10_2


printf "11. echo, flags: -p -s, file: "
if `diff sha256_test_results/sha256_10_1 sha256_test_results/sha256_10_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 12
echo "one more thing" | ../ft_ssl sha256 -r -p -s "foo" file -s "bar" > sha256_test_results/sha256_11_1 2> sha256_test_results/sha256_11_1_err
#echo "one more thing" | sha256 -r -p -s "foo" file -s "bar" > sha256_test_results/sha256_11_2 2> sha256_test_results/sha256_11_2_err

printf "one more thing
720bbf63077e0bea3b70c87954123daa6fcf32f973f4d646622bd016b140ec75
2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae \"foo\"
f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file\n" > sha256_test_results/sha256_11_2
printf "../ft_ssl: -s: No such file or directory\n../ft_ssl: bar: No such file or directory\n" > sha256_test_results/sha256_11_2_err

printf "12. echo, flags: -r -p -s, file, error files: "
if `diff sha256_test_results/sha256_11_1 sha256_test_results/sha256_11_2 > /dev/null`&&
 	`diff sha256_test_results/sha256_11_1_err sha256_test_results/sha256_11_2_err > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 13
echo "just to be extra clear" | ../ft_ssl sha256 -r -q -p -s "foo" file > sha256_test_results/sha256_12_1
#echo "just to be extra clear" | openssl sha256 file > sha256_test_results/sha256_12_2
printf "just to be extra clear
41c3da28172faf72bb777d6a428b6d801427d02513c56cd9e3672f44383f8eee
2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae
f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705\n" > sha256_test_results/sha256_12_2

printf "13. echo, flags: -r -q -p -s, file: "
if `diff sha256_test_results/sha256_12_1 sha256_test_results/sha256_12_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 14
echo "" | ../ft_ssl sha256 > sha256_test_results/sha256_14_1
echo "" | openssl sha -sha256 > sha256_test_results/sha256_14_2

printf "14. echo empty string: "
if `diff sha256_test_results/sha256_14_1 sha256_test_results/sha256_14_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 15
printf "\0\0\n" > testfile
cat testfile | ../ft_ssl sha256 > sha256_test_results/sha256_15_1
cat testfile | openssl sha -sha256 > sha256_test_results/sha256_15_2

printf "15. echo zero bytes: "
if `diff sha256_test_results/sha256_15_1 sha256_test_results/sha256_15_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 16
ls -lra /dev > testfile2
cat testfile2 | ../ft_ssl sha256 > sha256_test_results/sha256_16_1
cat testfile2 | openssl sha -sha256 > sha256_test_results/sha256_16_2

printf "16. ls -lra /dev: "
if `diff sha256_test_results/sha256_16_1 sha256_test_results/sha256_16_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi
