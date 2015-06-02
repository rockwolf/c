# Makefile

# Usage:
# ------
# make calculator_finance
# As root: make install
# make clean
# To remove:
# As root: make uninstall

CC = cc
CFLAGS = -g -O2 -W -Wall -Werror -Wextra
DEPS = calculator_finance.h types.h
OBJ = calculator_finance.o
TARGET = calculator_finance

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(TARGET).so $(.ALLSRC) -lm

$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c -fpic $(.PREFIX).c
	
install:
	cp -v calculator_finance.so /usr/local/lib/
	chmod 755 /usr/local/lib/calculator_finance.so
	
uninstall:
	rm -v /usr/local/lib/calculator_finance.so
	
.PHONY: clean

clean:
	rm -rfv calculator_finance.so *.o
