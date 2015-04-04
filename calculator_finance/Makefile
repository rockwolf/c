# Makefile

main: main.o calculator_finance.o unit_test.o general_functions.o
	cc -W -Wall -Werror -Wextra -o calculator_finance main.o calculator_finance.o unit_test.o general_functions.o

main.o: main.c main.h calculator_finance.h unit_test.h general_functions.h minunit.h
	cc -c main.c

clean:
	rm -rfv calculator_finance *.o
