mkdir des_test_results
echo ../orig > bigtest
YEL='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

# base64

../ft_ssl base64 -e -i bigtest -o des_test_results/eb64_1_1
base64 -i bigtest -o des_test_results/eb64_1_2
echo "des_test_results:"
printf "base64 encode: "
if `diff des_test_results/eb64_1_1 des_test_results/eb64_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl base64 -d -i des_test_results/eb64_1_2 -o des_test_results/db64_1_1
base64 -D -i des_test_results/eb64_1_2 -o des_test_results/db64_1_2
printf "base64 decode: "
if `diff des_test_results/db64_1_1 des_test_results/db64_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# ecb

../ft_ssl des-ecb -k 6162636461626364 -i bigtest -o des_test_results/eecb_1_1 -e
openssl des-ecb -K 6162636461626364 -in bigtest -out des_test_results/eecb_1_2

printf "des-ecb encode: "
if `diff des_test_results/eecb_1_1 des_test_results/eecb_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des-ecb -d -k 6162636461626364 -i des_test_results/eecb_1_1 -o des_test_results/decb_1_1
openssl des-ecb -d -K 6162636461626364 -in des_test_results/eecb_1_1 -out des_test_results/decb_1_2

printf "des-ecb decode: "
if `diff des_test_results/decb_1_1 des_test_results/decb_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des-ecb -k 6162636461626364 -i bigtest -o des_test_results/eecb_2_1 -e -a
openssl des-ecb -K 6162636461626364 -in bigtest -out des_test_results/eecb_2_2 -a

printf "des-ecb encode -a: "
if `diff des_test_results/eecb_2_1 des_test_results/eecb_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des-ecb -d -k 6162636461626364 -i des_test_results/eecb_2_1 -a -o des_test_results/decb_2_1
openssl des-ecb -d -K 6162636461626364 -in des_test_results/eecb_2_1 -a -out des_test_results/decb_2_2

printf "des-ecb decode -a: "
if `diff des_test_results/decb_2_2 des_test_results/decb_2_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# # cbc

../ft_ssl des-cbc -k 6162636461626364 -v 1122334455667788 -i bigtest -o des_test_results/ecbc_1_1
openssl des-cbc -K 6162636461626364 -iv 1122334455667788 -in bigtest -out des_test_results/ecbc_1_2

printf "des-cbc encode: "
if `diff des_test_results/ecbc_1_1 des_test_results/ecbc_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des-cbc -d -k 6162636461626364 -v 1122334455667788 -i des_test_results/ecbc_1_1 -o des_test_results/dcbc_1_1
openssl des-cbc -d -K 6162636461626364 -iv 1122334455667788 -in des_test_results/ecbc_1_1 -out des_test_results/dcbc_1_2

printf "des-cbc decode: "
if `diff des_test_results/dcbc_1_1 des_test_results/dcbc_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des-cbc -k 6162636461626364 -v 1122334455667788 -i bigtest -o des_test_results/ecbc_2_1 -a
openssl des-cbc -K 6162636461626364 -iv 1122334455667788 -in bigtest -out des_test_results/ecbc_2_2 -a

printf "des-cbc encode -a: "
if `diff des_test_results/ecbc_2_1 des_test_results/ecbc_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des-cbc -d -k 6162636461626364 -v 1122334455667788 -i des_test_results/ecbc_2_1 -a -o des_test_results/dcbc_2_1
openssl des-cbc -d -K 6162636461626364 -iv 1122334455667788 -in des_test_results/ecbc_2_1 -a -out des_test_results/dcbc_2_2

printf "des-cbc decode -a: "
if `diff des_test_results/dcbc_2_1 des_test_results/dcbc_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# des3-ecb

../ft_ssl des3-ecb -k 616263646162636411223344556677888877665544332211 -i bigtest -o des_test_results/eecb3_1_1
openssl des-ede3 -K 616263646162636411223344556677888877665544332211 -in bigtest -out des_test_results/eecb3_1_2

printf "des3-ecb encode: "
if `diff des_test_results/eecb3_1_1 des_test_results/eecb3_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des3-ecb -d -k 616263646162636411223344556677888877665544332211 -i des_test_results/eecb3_1_1 -o des_test_results/decb3_2_1
openssl des-ede3 -d -K 616263646162636411223344556677888877665544332211 -in des_test_results/eecb3_1_1 -out des_test_results/decb3_2_2

printf "des3-ecb decode: "
if `diff des_test_results/decb3_2_1 des_test_results/decb3_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des3-ecb -k 616263646162636411223344556677888877665544332211 -i bigtest -o des_test_results/eecb3_3_1 -a
openssl des-ede3 -K 616263646162636411223344556677888877665544332211 -in bigtest -out des_test_results/eecb3_3_2 -a

printf "des3-ecb encode -a: "
if `diff des_test_results/eecb3_3_1 des_test_results/eecb3_3_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des3-ecb -d -k 616263646162636411223344556677888877665544332211 -i des_test_results/eecb3_3_1 -a -o des_test_results/decb3_4_1
openssl des-ede3 -d -K 616263646162636411223344556677888877665544332211 -in des_test_results/eecb3_3_1 -a -out des_test_results/decb3_4_2

printf "des3-ecb encode -a: "
if `diff des_test_results/decb3_4_1 des_test_results/decb3_4_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# des3-cbc

../ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i bigtest -o des_test_results/ecbc3_1_1
openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in bigtest -out des_test_results/ecbc3_1_2

printf "des3-cbc encode: "
if `diff des_test_results/ecbc3_1_1 des_test_results/ecbc3_1_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i des_test_results/ecbc3_1_1 -o des_test_results/dcbc3_2_1
openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in des_test_results/ecbc3_1_1 -out des_test_results/cbcb3_2_2

printf "des3-cbc decode: "
if `diff des_test_results/decb3_2_1 des_test_results/decb3_2_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i bigtest -o des_test_results/ecbc3_3_1 -a
openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in bigtest -out des_test_results/ecbc3_3_2 -a

printf "des3-cbc encode -a: "
if `diff des_test_results/ecbc3_3_1 des_test_results/ecbc3_3_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i des_test_results/ecbc3_3_1 -a -o des_test_results/dcbc3_4_1
openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in des_test_results/ecbc3_3_1 -a -out des_test_results/dcbc3_4_2

printf "des3-cbc decode -a: "
if `diff des_test_results/dcbc3_4_1 des_test_results/dcbc3_4_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# encode/decode

../ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i bigtest | openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -out des_test_results/ed_1
printf "des3-cbc ft_encode/openssl_decode : "
if `diff bigtest des_test_results/ed_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

../ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i bigtest -a | openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -out des_test_results/ed_2 -a
printf "des3-cbc ft_encode/openssl_decode -a: "
if `diff bigtest des_test_results/ed_2 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in bigtest | ../ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -o des_test_results/ed_3
printf "des3-cbc openssl_encode/ft_decode: "
if `diff bigtest des_test_results/ed_3 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

openssl des3 -K 616263646162636411223344556677888877665544332211 -a -iv 1122334455667788 -in bigtest | ../ft_ssl des3-cbc -a -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -o des_test_results/ed_4
printf "des3-cbc openssl_encode/ft_decode -a: "
if `diff bigtest des_test_results/ed_4 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

printf "\n"

# input/output
echo "some text to test input" > des_test_results/io_1

echo "some text to test input" | ../ft_ssl base64 | ../ft_ssl base64 -d > des_test_results/io_2
printf "b64 input/output stream test: "
if `diff des_test_results/io_2 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ../ft_ssl des-ecb -k 6162636461626364 | ../ft_ssl des-ecb -d -k 6162636461626364 > des_test_results/io_3_2
printf "ecb input/output stream test: "
if `diff des_test_results/io_3_2 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ../ft_ssl des-ecb -k 6162636461626364 -a | ../ft_ssl des-ecb -d -k 6162636461626364 -a > des_test_results/io_3
printf "ecb input/output stream test -a: "
if `diff des_test_results/io_3 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ../ft_ssl des-cbc -k 6162636461626364 -v 1122334455667788 | ../ft_ssl des-cbc -d -k 6162636461626364 -v 1122334455667788 > des_test_results/io_4
printf "cbc input/output stream test: "
if `diff des_test_results/io_4 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ../ft_ssl des-cbc -k 6162636461626364 -v 1122334455667788 -a | ../ft_ssl des-cbc -d -k 6162636461626364 -v 1122334455667788 -a > des_test_results/io_4_2
printf "cbc input/output stream test -a: "
if `diff des_test_results/io_4_2 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ../ft_ssl des3-ecb -k 616263646162636411223344556677888877665544332211 | ../ft_ssl des3-ecb -d -k 616263646162636411223344556677888877665544332211 > des_test_results/io_5
printf "des3-ecb input/output stream test: "
if `diff des_test_results/io_5 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ../ft_ssl des3-ecb -a -k 616263646162636411223344556677888877665544332211 | ../ft_ssl des3-ecb -a -d -k 616263646162636411223344556677888877665544332211 > des_test_results/io_5_2
printf "des3-ecb input/output stream test -a: "
if `diff des_test_results/io_5_2 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ../ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 | ../ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 > des_test_results/io_6
printf "des3-cbc input/output stream test: "
if `diff des_test_results/io_6 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

echo "some text to test input" | ../ft_ssl des3-cbc -a -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 | ../ft_ssl des3-cbc -a -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 > des_test_results/io_6_2
printf "des3-cbc input/output stream test -a: "
if `diff des_test_results/io_6_2 des_test_results/io_1 > /dev/null`; then
echo "${YEL}OK${NC}"
else
echo "${RED}FAIL${NC}"
fi

# time
# printf "ft_ssl 10mb file: "
# time ../ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i orig -a | ../ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -a -o /dev/null

# printf "openssl 10mb file: "
# time openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in orig -a | openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -a -out /dev/null

# printf "\n"

# printf "ft_ssl encode: "
# time ../ft_ssl des3-cbc -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -i orig -a -o des_test_results/out

# printf "openssl encode: "
# time openssl des3 -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -in orig -a -out des_test_results/out

# printf "\n"
# printf "ft_ssl decode: "
# time ../ft_ssl des3-cbc -d -k 616263646162636411223344556677888877665544332211 -v 1122334455667788 -a -i des_test_results/out -o /dev/null

# printf "openssl decode: "
# time openssl des3 -d -K 616263646162636411223344556677888877665544332211 -iv 1122334455667788 -a -in des_test_results/out -out /dev/null
