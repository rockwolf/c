# Makefile

# Usage:
# ------
# make libcalculatorfinance
# As root: make install
# make clean
# To remove:
# As root: make uninstall

CC = cc
CFLAGS = -g -O2 -W -Wall -Werror -Wextra
DEPS = libcalculatorfinance.h types.h
OBJ = libcalculatorfinance.o
TARGET = libcalculatorfinance

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(TARGET).so $(.ALLSRC) -lm
   #	-lcalculatorfinance

$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c -fpic $(.PREFIX).c
	
install:
	cp -v libcalculatorfinance.so /usr/local/lib/
	chmod 755 /usr/local/lib/libcalculatorfinance.so
	
uninstall:
	rm -v /usr/local/lib/libcalculatorfinance.so
	
.PHONY: clean

clean:
	rm -rfv libcalculatorfinance.so *.o
