all: ProjetAA
ProjetAA : ProjetAA.c
	gcc -Wall -Wextra -Wfatal-errors -g  ProjetAA.c -o ProjetAA
	./ProjetAA
clean:
	rm -f *.o ProjetAA