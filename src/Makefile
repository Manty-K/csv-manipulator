CFLAGS = -g -Wextra

all: e.o
	./e.o -c test.csv -r trules.txt -o out.csv


e.o: csv.tab.c rules.tab.c lex.csv.c lex.rules.c main.c
	gcc $(CFLAGS) csv.tab.c rules.tab.c lex.csv.c lex.rules.c main.c -o e.o


lex.csv.c: csv.l
	flex csv.l

csv.tab.c: csv.y
	bison -d csv.y

lex.rules.c: rules.l
	flex rules.l

rules.tab.c: rules.y
	bison -d rules.y


clean:
	rm -rf lex.* *.tab.* *.o