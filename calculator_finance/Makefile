# libcalculatorfinance
# See LICENSE file for copyright and license details.

# Usage:
# ------
# make libcalculatorfinance
# As root: make install
# make clean
# To remove:
# As root: make uninstall

include config.mk

SRC = ledgerplot.c functions.c income_vs_expenses.c
OBJ = ${SRC:.c=.o}
VPATH = .:modules
DEPS = libcalculatorfinance.h types.
TARGET = libcalculatorfinance

all: options ${TARGET}

options:
	@echo libcalculatorfinance build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"
	
.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<
	
${OBJ}: config.h config.mk

# TODO: finish porting the below to the makefile structure of the ledgerplot application.
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(TARGET).so $(.ALLSRC) -lm
   #	-lcalculatorfinance

$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c -fpic $(.PREFIX).c
	
install:
	@echo installing library to /usr/local/lib
	cp -v libcalculatorfinance.so /usr/local/lib/
	chmod 755 /usr/local/lib/libcalculatorfinance.so
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < libcalculatorfinance.1 > ${DESTDIR}${MANPREFIX}/man1/libcalculatorfinance.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/libcalculatorfinance.1
	
uninstall:
	@echo removing library from /usr/local/lib
	rm -v /usr/local/lib/libcalculatorfinance.so
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/libcalculatorfinance.1
	
.PHONY: clean

clean:
	rm -rfv libcalculatorfinance.so *.o
