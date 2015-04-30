# Makefile
CC = cc
CFLAGS = -g -O2 -W -Wall -Werror -Wextra -lcalculator_finance
DEPS = main.h const.h unit_test.h unit_test_trade.h general_functions.h minunit.h
OBJ = main.o unit_test.o unit_test_trade.o general_functions.o

$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c $(.PREFIX).c
	
test: $(OBJ)
	$(CC) $(CFLAGS) -o $(.TARGET) $(.ALLSRC) -lm

.PHONY: clean

clean:
	rm -rfv test *.o
