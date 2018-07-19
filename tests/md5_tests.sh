mkdir md5_test_results
cat md5_tests.sh > bigtest
YEL='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo
echo "-----------------"
echo "MD5 test results:"
echo "-----------------"
# MD5

# 1
echo "pickle rick" | ../ft_ssl md5 > md5_test_results/md5_1_1
echo "pickle rick" | md5 > md5_test_results/md5_1_2

printf "1. echo: "
if `diff md5_test_results/md5_1_1 md5_test_results/md5_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 2
echo "Do not pity the dead, Harry." | ../ft_ssl md5 -p > md5_test_results/md5_2_1
echo "Do not pity the dead, Harry." | md5 -p > md5_test_results/md5_2_2

printf "2. echo, flags: -p: "
if `diff md5_test_results/md5_2_1 md5_test_results/md5_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 3
echo "Pity the living." | ../ft_ssl md5 -q -r > md5_test_results/md5_3_1
echo "Pity the living." | md5 -q -r > md5_test_results/md5_3_2

printf "3. echo, flags: -p -r: "
if `diff md5_test_results/md5_3_1 md5_test_results/md5_3_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 4
echo "And above all," > file
../ft_ssl md5 file > md5_test_results/md5_4_1
md5 file > md5_test_results/md5_4_2

printf "4. file: "
if `diff md5_test_results/md5_4_1 md5_test_results/md5_4_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 5
../ft_ssl md5 -r file > md5_test_results/md5_5_1
md5 -r file > md5_test_results/md5_5_2

printf "5. file, flags: -r: "
if `diff md5_test_results/md5_5_1 md5_test_results/md5_5_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 6
../ft_ssl md5 -s "pity those that aren't following baerista on spotify." > md5_test_results/md5_6_1
md5 -s "pity those that aren't following baerista on spotify." > md5_test_results/md5_6_2

printf "6. flags: -s: "
if `diff md5_test_results/md5_6_1 md5_test_results/md5_6_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 7
echo "be sure to handle edge cases carefully" | ../ft_ssl md5 -p file > md5_test_results/md5_7_1
echo "be sure to handle edge cases carefully" | md5 -p file > md5_test_results/md5_7_2

printf "7. echo, flags: -p, file: "
if `diff md5_test_results/md5_7_1 md5_test_results/md5_7_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 8
echo "some of this will not make sense at first" | ../ft_ssl md5 file > md5_test_results/md5_8_1
echo "some of this will not make sense at first" | md5 file > md5_test_results/md5_8_2

printf "8. echo, file: "
if `diff md5_test_results/md5_8_1 md5_test_results/md5_8_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 9
echo "but eventually you will understand" | ../ft_ssl md5 -p -r file > md5_test_results/md5_9_1
echo "but eventually you will understand" | md5 -p -r file > md5_test_results/md5_9_2

printf "9. echo, flags: -p -r, file: "
if `diff md5_test_results/md5_9_1 md5_test_results/md5_9_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 10
echo "GL HF let's go" | ../ft_ssl md5 -p -s "foo" file > md5_test_results/md5_10_1
echo "GL HF let's go" | md5 -p -s "foo" file > md5_test_results/md5_10_2

printf "10. echo, flags: -p -s, file: "
if `diff md5_test_results/md5_10_1 md5_test_results/md5_10_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 11
echo "one more thing" | ../ft_ssl md5 -r -p -s "foo" file -s "bar" > md5_test_results/md5_11_1 2> md5_test_results/md5_11_1_err
echo "one more thing" | md5 -r -p -s "foo" file -s "bar" > md5_test_results/md5_11_2 2> md5_test_results/md5_11_2_err

printf "11. echo, flags: -r -p -s, file, error files: "
# if `diff md5_test_results/md5_11_1 md5_test_results/md5_11_2 > /dev/null`&&
# 	`diff md5_test_results/md5_11_1_err md5_test_results/md5_11_2_err > /dev/null`; then
if `diff md5_test_results/md5_11_1 md5_test_results/md5_11_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# 12
echo "just to be extra clear" | ../ft_ssl md5 -r -q -p -s "foo" file > md5_test_results/md5_12_1
echo "just to be extra clear" | md5 -r -q -p -s "foo" file > md5_test_results/md5_12_2

printf "12. echo, flags: -r -q -p -s, file: "
if `diff md5_test_results/md5_12_1 md5_test_results/md5_12_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi
