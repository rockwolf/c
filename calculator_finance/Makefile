# Makefile

# Usage:
#
# make calculator_finance
# As root: make install
# make clean
# To remove:
# As root: make uninstall

CC = cc
CFLAGS = -g -O2 -W -Wall -Werror -Wextra
DEPS = main.h const.h calculator_finance.h unit_test.h unit_test_trade.h general_functions.h minunit.h
OBJ = main.o calculator_finance.o unit_test.o unit_test_trade.o general_functions.o

$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c -fpic $(.PREFIX).c
	
calculator_finance: $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(.TARGET).so $(.ALLSRC) -lm

install:
	cp -v calculator_finance.so /usr/local/lib/
	chmod 755 /usr/local/lib/calculator_finance.so
	
uninstall:
	rm -v /usr/local/lib/calculator_finance.so
	
.PHONY: clean

clean:
	rm -rfv calculator_finance.so *.o
