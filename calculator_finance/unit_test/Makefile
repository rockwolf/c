# Makefile
# TODO: remove the unneeded stuff + add -l option to use the shared library.
CC = cc
CFLAGS = -g -O2 -W -Wall -Werror -Wextra
DEPS = main.h const.h unit_test.h unit_test_trade.h general_functions.h minunit.h
OBJ = main.o calculator_finance.o unit_test.o unit_test_trade.o general_functions.o

$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c -fpic $(.PREFIX).c
	
calculator_finance: $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(.TARGET).so $(.ALLSRC) -lm

.PHONY: clean

clean:
	rm -rfv calculator_finance.so *.o
