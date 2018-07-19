rm -rf sha512_test_results
mkdir sha512_test_results
cat orig > bigtest
YEL='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo "--------------------"
echo "SHA512 test results:"
echo "--------------------"
# sha512

# 1
echo "pickle rick" | ../ft_ssl sha512 > sha512_test_results/sha512_1_1
echo "pickle rick" | openssl sha -sha512 > sha512_test_results/sha512_1_2

printf "1. echo: "
if `diff sha512_test_results/sha512_1_1 sha512_test_results/sha512_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 2
cat bigtest | ../ft_ssl sha512 > sha512_test_results/sha512_1_1_1
cat bigtest | openssl sha -sha512 > sha512_test_results/sha512_1_2_1

printf "2. echo bigtest: "
if `diff sha512_test_results/sha512_1_1 sha512_test_results/sha512_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 3
echo "Do not pity the dead, Harry." | ../ft_ssl sha512 -p > sha512_test_results/sha512_2_1
echo "Do not pity the dead, Harry." > sha512_test_results/sha512_2_2
echo "Do not pity the dead, Harry." | openssl sha512 >> sha512_test_results/sha512_2_2

printf "3. echo, flags: -p: "
if `diff sha512_test_results/sha512_2_1 sha512_test_results/sha512_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 4
echo "Pity the living." | ../ft_ssl sha512 -q -r > sha512_test_results/sha512_3_1
echo "Pity the living." | openssl sha512 > sha512_test_results/sha512_3_2

printf "4. echo, flags: -p -r: "
if `diff sha512_test_results/sha512_3_1 sha512_test_results/sha512_3_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 5
echo "And above all," > file
../ft_ssl sha512 file > sha512_test_results/sha512_4_1
printf "SHA512 (file) = " > sha512_test_results/sha512_4_2
cat file | openssl sha512 >> sha512_test_results/sha512_4_2

printf "5. file: "
if `diff sha512_test_results/sha512_4_1 sha512_test_results/sha512_4_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 6
../ft_ssl sha512 -r file > sha512_test_results/sha512_5_1
cat file | openssl sha512 > sha512_test_results/sha512_5_2
printf %s "$(< sha512_test_results/sha512_5_2)" > sha512_test_results/sha512_5_2
printf " file\n" >> sha512_test_results/sha512_5_2

printf "6. file, flags: -r: "
if `diff sha512_test_results/sha512_5_1 sha512_test_results/sha512_5_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 7
../ft_ssl sha512 -s "pity those that aren't following baerista on spotify." > sha512_test_results/sha512_6_1
printf "SHA512 (\"pity those that aren't following baerista on spotify.\") = " > sha512_test_results/sha512_6_2
printf "pity those that aren't following baerista on spotify." | openssl sha512 >> sha512_test_results/sha512_6_2

printf "7. flags: -s: "
if `diff sha512_test_results/sha512_6_1 sha512_test_results/sha512_6_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 8
echo "be sure to handle edge cases carefully" | ../ft_ssl sha512 -p file > sha512_test_results/sha512_7_1
echo "be sure to handle edge cases carefully" > sha512_test_results/sha512_7_2
echo "be sure to handle edge cases carefully" | openssl sha512 >> sha512_test_results/sha512_7_2
printf "SHA512 (file) = " >> sha512_test_results/sha512_7_2
cat file | openssl sha512 >> sha512_test_results/sha512_7_2

printf "8. echo, flags: -p, file: "
if `diff sha512_test_results/sha512_7_1 sha512_test_results/sha512_7_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 9
echo "some of this will not make sense at first" | ../ft_ssl sha512 file > sha512_test_results/sha512_8_1
printf "SHA512 (file) = " > sha512_test_results/sha512_8_2
cat file | openssl sha512 >> sha512_test_results/sha512_8_2

printf "9. echo, file: "
if `diff sha512_test_results/sha512_8_1 sha512_test_results/sha512_8_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 10
echo "but eventually you will understand" | ../ft_ssl sha512 -p -r file > sha512_test_results/sha512_9_1
echo "but eventually you will understand" > sha512_test_results/sha512_9_2
echo "but eventually you will understand" | openssl sha512 >> sha512_test_results/sha512_9_2
cat file | openssl sha512 >> sha512_test_results/sha512_9_2
printf %s "$(< sha512_test_results/sha512_9_2)" > sha512_test_results/sha512_9_2
printf " file\n" >> sha512_test_results/sha512_9_2

printf "10. echo, flags: -p -r, file: "
if `diff sha512_test_results/sha512_9_1 sha512_test_results/sha512_9_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 11
echo "GL HF let's go" | ../ft_ssl sha512 -p -s "foo" file > sha512_test_results/sha512_10_1
echo "GL HF let's go" > sha512_test_results/sha512_10_2
echo "GL HF let's go" | openssl sha512 >> sha512_test_results/sha512_10_2
printf "SHA512 (\"foo\") = " >> sha512_test_results/sha512_10_2
printf "foo" | openssl sha512 >> sha512_test_results/sha512_10_2
printf "SHA512 (file) = " >> sha512_test_results/sha512_10_2
cat file | openssl sha512 >> sha512_test_results/sha512_10_2

printf "11. echo, flags: -p -s, file: "
if `diff sha512_test_results/sha512_10_1 sha512_test_results/sha512_10_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# # 12
# echo "one more thing" | ../ft_ssl sha512 -r -p -s "foo" file -s "bar" > sha512_test_results/sha512_11_1 2> sha512_test_results/sha512_11_1_err
# #echo "one more thing" | sha512 -r -p -s "foo" file -s "bar" > sha512_test_results/sha512_11_2 2> sha512_test_results/sha512_11_2_err

# printf "one more thing
# 720bbf63077e0bea3b70c87954123daa6fcf32f973f4d646622bd016b140ec75
# 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae \"foo\"
# f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file\n" > sha512_test_results/sha512_11_2
# printf "../ft_ssl: -s: No such file or directory\n../ft_ssl: bar: No such file or directory\n" > sha512_test_results/sha512_11_2_err

# printf "12. echo, flags: -r -p -s, file, error files: "
# if `diff sha512_test_results/sha512_11_1 sha512_test_results/sha512_11_2 > /dev/null`&&
#  	`diff sha512_test_results/sha512_11_1_err sha512_test_results/sha512_11_2_err > /dev/null`; then
# echo "${YEL}OK${NC}"
# else
# echo "${RED}FAIL${NC}"
# fi

# # 13
# echo "just to be extra clear" | ../ft_ssl sha512 -r -q -p -s "foo" file > sha512_test_results/sha512_12_1
# #echo "just to be extra clear" | openssl sha512 file > sha512_test_results/sha512_12_2
# printf "just to be extra clear
# 41c3da28172faf72bb777d6a428b6d801427d02513c56cd9e3672f44383f8eee
# 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae
# f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705\n" > sha512_test_results/sha512_12_2

# printf "13. echo, flags: -r -q -p -s, file: "
# if `diff sha512_test_results/sha512_12_1 sha512_test_results/sha512_12_2 > /dev/null`; then
# echo "${YEL}OK${NC}"
# else
# echo "${RED}FAIL${NC}"
# fi

# # 14
# echo "" | ../ft_ssl sha512 > sha512_test_results/sha512_14_1
# echo "" | openssl sha -sha512 > sha512_test_results/sha512_14_2

# printf "14. echo empty string: "
# if `diff sha512_test_results/sha512_14_1 sha512_test_results/sha512_14_2 > /dev/null`; then
# echo "${YEL}OK${NC}"
# else
# echo "${RED}FAIL${NC}"
# fi

# # 15
# printf "\0\0\n" > testfile
# cat testfile | ../ft_ssl sha512 > sha512_test_results/sha512_15_1
# cat testfile | openssl sha -sha512 > sha512_test_results/sha512_15_2

# printf "15. echo zero bytes: "
# if `diff sha512_test_results/sha512_15_1 sha512_test_results/sha512_15_2 > /dev/null`; then
# echo "${YEL}OK${NC}"
# else
# echo "${RED}FAIL${NC}"
# fi

# # 16
# ls -lra /dev > testfile2
# cat testfile2 | ../ft_ssl sha512 > sha512_test_results/sha512_16_1
# cat testfile2 | openssl sha -sha512 > sha512_test_results/sha512_16_2

# printf "16. ls -lra /dev: "
# if `diff sha512_test_results/sha512_16_1 sha512_test_results/sha512_16_2 > /dev/null`; then
# echo "${YEL}OK${NC}"
# else
# echo "${RED}FAIL${NC}"
# fi
