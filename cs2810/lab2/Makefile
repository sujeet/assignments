# Beginning of Makefile

CC = g++
ll_int_option = -D BASE=100000000 -D WIDTH=8 -D TYPE=long\ long\ int
strict_option = -Wall -pedantic

# bigint which uses int datatype for storage

bigint : bigint_prog_int.o BigInt_int.o IntList_int.o
	$(CC) -o $@ bigint_prog_int.o BigInt_int.o IntList_int.o 

bigint_prog_int.o : bigint_prog.cpp BigInt.h
	$(CC) -o $@ -c $< $(strict_option)

BigInt_int.o : BigInt.cpp BigInt.h IntList.h
	$(CC) -o $@ -c $< $(strict_option)

IntList_int.o : IntList.cpp IntList.h
	$(CC) -o $@ -c $< $(strict_option)

clean :
	rm bigint bigint_prog_int.o \
		BigInt_int.o IntList_int.o


# bigint which uses long long int datatype for storage

bigint_ll : bigint_prog_llint.o BigInt_llint.o IntList_llint.o
	$(CC) -o $@ bigint_prog_llint.o BigInt_llint.o IntList_llint.o

bigint_prog_llint.o : bigint_prog.cpp BigInt.h
	$(CC) -o $@ -c $< $(ll_int_option)

BigInt_llint.o : BigInt.cpp BigInt.h IntList.h
	$(CC) -o $@ -c $< $(ll_int_option)

IntList_llint.o : IntList.cpp IntList.h
	$(CC) -o $@ -c $< $(ll_int_option)

clean_ll :
	rm bigint_ll bigint_prog_llint.o \
		BigInt_llint.o IntList_llint.o

# End of Makefile
