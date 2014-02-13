# Makefile

#CPPFLAGS += -I/usr/local/include

celinda: celinda.c
	#gcc -W -Wall -Werror -Wextra -o celinda celinda.c -lncurses
	#cc -W -Werror -Wextra -lpq -o celinda celinda.c
	#TODO: try this:
	cc -I/usr/local/include -L/usr/local/lib/postgresql -o celinda -lpq celinda.c
	#gcc49 -o celinda -I/usr/local/include/ -lpq celinda.c


clean:
	rm -rfv celinda *.o
