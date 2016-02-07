# Makefile
CC = cc
CFLAGS = -v -g -O2 -W -Wall -Werror -Wextra
DEPS = main.h const.h types.h unit_test.h unit_test_trade.h general_functions.h minunit.h
OBJ = main.o unit_test.o unit_test_trade.o general_functions.o
TARGET = main 
FILENAME = test

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(FILENAME) $(.ALLSRC) -lm -L/usr/local/lib/ -lcalculatorfinance

$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c $(.PREFIX).c
	
.PHONY: clean

clean:
	rm -rfv test *.o
