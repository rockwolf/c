# Makefile
hina: hina.c
	#gcc -W -Wall -Werror -Wextra -o hina hina.c -lncurses
	cc -std=c99 -W -Wall -Werror -Wextra -o hina hina.c -ledit -ltermcap

clean:
	rm -rfv hina *.o
