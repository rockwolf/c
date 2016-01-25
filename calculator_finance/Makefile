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

SRC = libcalculatorfinance.c
OBJ = ${SRC:.c=.o}
VPATH = .:modules
DEPS = libcalculatorfinance.h types.h
TARGET = libcalculatorfinance

all: options ${TARGET}

options:
	@echo libcalculatorfinance build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"
	
.c.o:
	@echo CC $<
	@${CC} -c -fpic ${CFLAGS} $<
	
#${OBJ}: config.mk ${DEPS} 

#TODO: replace the below
$(OBJ): $(.PREFIX).c $(DEPS)
	$(CC) $(CFLAGS) -c -fpic $(.PREFIX).c

$(TARGET): ${OBJ}
	@echo CC -o $@.so -shared ${OBJ} ${LDFLAGS}
	@${CC} -o $@.so -shared ${OBJ} ${LDFLAGS}
# TODO: finish porting the below to the makefile structure of the ledgerplot application.
#$(TARGET): $(OBJ)
#	$(CC) $(CFLAGS) -shared -o $(TARGET).so $(.ALLSRC) -lm
#   #	-lcalculatorfinance
   
clean:
	@echo cleaning...
	@rm -fv ${TARGET}.so ${OBJ} ${TARGET}-${VERSION}.tar.gz
	
dist: clean
	@echo creating dist tarball
	@mkdir -p ${TARGET}-${VERSION}
	@cp -R LICENSE.txt Makefile README.adoc config.mk \
		libcalculatorfinance.1 libcalculatorfinance.h types.h ${SRC} unit_test/ ${TARGET}-${VERSION}
	@tar -cf ${TARGET}-${VERSION}.tar ${TARGET}-${VERSION}
	@gzip ${TARGET}-${VERSION}.tar
	@rm -rf ${TARGET}-${VERSION}

install: all
	@echo installing library to ${DESTDIR}${PREFIX}/lib
	@mkdir -p ${DESTDIR}${PREFIX}/lib
	@cp -f ${TARGET}.so ${DESTDIR}${PREFIX}/lib
	@chmod 755 ${DESTDIR}${PREFIX}/lib/${TARGET}
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < libcalculatorfinance.1 > ${DESTDIR}${MANPREFIX}/man1/${TARGET}.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/${TARGET}.1
	
uninstall:
	@echo removing library from ${DESTDIR}${PREFIX}/lib
	@rm -f ${DESTDIR}${PREFIX}/lib/${TARGET}.so
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/${TARGET}.1
	
.PHONY: all options clean dist install uninstall
