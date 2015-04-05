# Makefile

CC = cc
CFLAGS = -g -O2 -W -Wall -Werror -Wextra
DEPS = main.h calculator_finance.h unit_test.h unit_test_trade.h general_functions.h minunit.h
OBJ = main.o calculator_finance.o unit_test.o unit_test_trade.o general_functions.o

calculator_finance: $(OBJ)
	$(CC) $(CFLAGS) -o $(.TARGET) $(.ALLSRC)

$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c $(.PREFIX).c

.PHONY: clean

clean:
	rm -rfv calculator_finance *.o
