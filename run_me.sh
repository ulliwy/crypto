mkdir tests
YEL='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'
# base64

./ft_ssl base64 -e -i bigtest -o tests/eb64_1_1
base64 -i bigtest -o tests/eb64_1_2
echo "Tests:"
printf "base64 encode: "
if `diff tests/eb64_1_1 tests/eb64_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl base64 -d -i tests/eb64_1_1 -o tests/db64_1_1
base64 -D -i tests/eb64_1_1 -o tests/db64_1_2
printf "base64 decode: "
if `diff tests/db64_1_1 tests/db64_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# ecb

./ft_ssl des-ecb -k 6162636461626364 -i bigtest -o tests/eecb_1_1 -e
openssl des-ecb -K 6162636461626364 -in bigtest -out tests/eecb_1_2

printf "des-ecb encode: "
if `diff tests/eecb_1_1 tests/eecb_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des-ecb -d -k 6162636461626364 -i tests/eecb_1_1 -o tests/decb_1_1
openssl des-ecb -d -K 6162636461626364 -in tests/eecb_1_1 -out tests/decb_1_2

printf "des-ecb decode: "
if `diff tests/decb_1_1 tests/decb_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des-ecb -k 6162636461626364 -i bigtest -o tests/eecb_2_1 -e -a
openssl des-ecb -K 6162636461626364 -in bigtest -out tests/eecb_2_2 -a

printf "des-ecb encode -a: "
if `diff tests/eecb_2_1 tests/eecb_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des-ecb -d -k 6162636461626364 -i tests/eecb_2_1 -a -o tests/decb_2_1
openssl des-ecb -d -K 6162636461626364 -in tests/eecb_2_1 -a -out tests/decb_2_2

printf "des-ecb decode -a: "
if `diff tests/decb_2_2 tests/decb_2_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# cbc

./ft_ssl des-cbc -k 6162636461626364 -v 1122334455667788 -i bigtest -o tests/ecbc_1_1
openssl des-cbc -K 6162636461626364 -iv 1122334455667788 -in bigtest -out tests/ecbc_1_2

printf "des-cbc encode: "
if `diff tests/ecbc_1_1 tests/ecbc_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des-cbc -d -k 6162636461626364 -v 1122334455667788 -i tests/ecbc_1_1 -o tests/dcbc_1_1
openssl des-cbc -d -K 6162636461626364 -iv 1122334455667788 -in tests/ecbc_1_1 -out tests/dcbc_1_2

printf "des-cbc decode: "
if `diff tests/dcbc_1_1 tests/dcbc_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des-cbc -k 6162636461626364 -v 1122334455667788 -i bigtest -o tests/ecbc_2_1 -a
openssl des-cbc -K 6162636461626364 -iv 1122334455667788 -in bigtest -out tests/ecbc_2_2 -a

printf "des-cbc encode -a: "
if `diff tests/ecbc_2_1 tests/ecbc_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des-cbc -d -k 6162636461626364 -v 1122334455667788 -i tests/ecbc_2_1 -a -o tests/dcbc_2_1
openssl des-cbc -d -K 6162636461626364 -iv 1122334455667788 -in tests/ecbc_2_1 -a -out tests/dcbc_2_2

printf "des-cbc decode -a: "
if `diff tests/dcbc_2_1 tests/dcbc_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# des3-ecb

./ft_ssl des3-ecb -k 616263646162636411223344556677888877665544332211 -i bigtest -o tests/eecb3_1_1
openssl des-ede3 -K 616263646162636411223344556677888877665544332211 -in bigtest -out tests/eecb3_1_2

printf "des3-ecb encode: "
if `diff tests/eecb3_1_1 tests/eecb3_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des3-ecb -d -k 616263646162636411223344556677888877665544332211 -i tests/eecb3_1_1 -o tests/decb3_2_1
openssl des-ede3 -d -K 616263646162636411223344556677888877665544332211 -in tests/eecb3_1_1 -out tests/decb3_2_2

printf "des3-ecb decode: "
if `diff tests/decb3_2_1 tests/decb3_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des3-ecb -k 616263646162636411223344556677888877665544332211 -i bigtest -o tests/eecb3_3_1 -a
openssl des-ede3 -K 616263646162636411223344556677888877665544332211 -in bigtest -out tests/eecb3_3_2 -a

printf "des3-ecb encode -a: "
if `diff tests/eecb3_3_1 tests/eecb3_3_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des3-ecb -d -k 616263646162636411223344556677888877665544332211 -i tests/eecb3_3_1 -a -o tests/decb3_4_1
openssl des-ede3 -d -K 616263646162636411223344556677888877665544332211 -in tests/eecb3_3_1 -a -out tests/decb3_4_2

printf "des3-ecb encode -a: "
if `diff tests/decb3_4_1 tests/decb3_4_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# des3-cbc

./ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i bigtest -o tests/ecbc3_1_1
openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in bigtest -out tests/ecbc3_1_2

printf "des3-cbc encode: "
if `diff tests/ecbc3_1_1 tests/ecbc3_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i tests/ecbc3_1_1 -o tests/dcbc3_2_1
openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in tests/ecbc3_1_1 -out tests/cbcb3_2_2

printf "des3-cbc decode: "
if `diff tests/decb3_2_1 tests/decb3_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i bigtest -o tests/ecbc3_3_1 -a
openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in bigtest -out tests/ecbc3_3_2 -a

printf "des3-cbc encode -a: "
if `diff tests/ecbc3_3_1 tests/ecbc3_3_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i tests/ecbc3_3_1 -a -o tests/dcbc3_4_1
openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in tests/ecbc3_3_1 -a -out tests/dcbc3_4_2

printf "des3-cbc decode -a: "
if `diff tests/dcbc3_4_1 tests/dcbc3_4_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# encode/decode

./ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i orig | openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -out tests/ed_1
printf "des3-cbc ft_encode/openssl_decode : "
if `diff orig tests/ed_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

./ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i orig -a | openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -out tests/ed_2 -a
printf "des3-cbc ft_encode/openssl_decode -a: "
if `diff orig tests/ed_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in orig | ./ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -o tests/ed_3
printf "des3-cbc openssl_encode/ft_decode: "
if `diff orig tests/ed_3 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

openssl des3 -K 616263646162636411223344556677888877665544332211 -a -iv 1122334455667788 -in orig | ./ft_ssl des3-cbc -a -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -o tests/ed_4
printf "des3-cbc openssl_encode/ft_decode -a: "
if `diff orig tests/ed_4 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# input/output
echo "some text to test input" > tests/io_1

echo "some text to test input" | ./ft_ssl base64 | ./ft_ssl base64 -d > tests/io_2
printf "b64 input/output stream test: "
if `diff tests/io_2 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ./ft_ssl des-ecb -k 6162636461626364 | ./ft_ssl des-ecb -d -k 6162636461626364 > tests/io_3_2
printf "ecb input/output stream test: "
if `diff tests/io_3_2 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ./ft_ssl des-ecb -k 6162636461626364 -a | ./ft_ssl des-ecb -d -k 6162636461626364 -a > tests/io_3
printf "ecb input/output stream test -a: "
if `diff tests/io_3 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ./ft_ssl des-cbc -k 6162636461626364 -v 1122334455667788 | ./ft_ssl des-cbc -d -k 6162636461626364 -v 1122334455667788 > tests/io_4
printf "cbc input/output stream test: "
if `diff tests/io_4 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ./ft_ssl des-cbc -k 6162636461626364 -v 1122334455667788 -a | ./ft_ssl des-cbc -d -k 6162636461626364 -v 1122334455667788 -a > tests/io_4_2
printf "cbc input/output stream test -a: "
if `diff tests/io_4_2 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ./ft_ssl des3-ecb -k 616263646162636411223344556677888877665544332211 | ./ft_ssl des3-ecb -d -k 616263646162636411223344556677888877665544332211 > tests/io_5
printf "des3-ecb input/output stream test: "
if `diff tests/io_5 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ./ft_ssl des3-ecb -a -k 616263646162636411223344556677888877665544332211 | ./ft_ssl des3-ecb -a -d -k 616263646162636411223344556677888877665544332211 > tests/io_5_2
printf "des3-ecb input/output stream test -a: "
if `diff tests/io_5_2 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ./ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 | ./ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 > tests/io_6
printf "des3-cbc input/output stream test: "
if `diff tests/io_6 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ./ft_ssl des3-cbc -a -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 | ./ft_ssl des3-cbc -a -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 > tests/io_6_2
printf "des3-cbc input/output stream test -a: "
if `diff tests/io_6_2 tests/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# time
# printf "ft_ssl 10mb file: "
# time ./ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i orig -a | ./ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -a -o /dev/null

# printf "openssl 10mb file: "
# time openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in orig -a | openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -a -out /dev/null

# printf "\n"

# printf "ft_ssl encode: "
# time ./ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i orig -a -o tests/out

# printf "openssl encode: "
# time openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in orig -a -out tests/out

# printf "\n"
# printf "ft_ssl decode: "
# time ./ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -a -i tests/out -o /dev/null

# printf "openssl decode: "
# time openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -a -in tests/out -out /dev/null
