CFLAGS = -g -Wextra

DATA_STRUTS = data-structures/array/array.c data-structures/queue/queue.c data-structures/stack/stack.c data-structures/tree/tree.c

DEPS = csv.tab.c rules.tab.c lex.csv.c lex.rules.c main.c csv-controller/csv-controller.c csv-controller/csv-data.c output/output.c  rules-controller/rules-controller.c rules-controller/expression-handler.c rules-controller/functions.c $(DATA_STRUTS)

all: e.o
	./e.o -c test.csv -r trules.txt -o out.csv


e.o: $(DEPS)
	gcc $(CFLAGS) $(DEPS) -o e.o


lex.csv.c: csv.l
	flex csv.l

csv.tab.c: csv.y
	bison -d -Wcounterexamples csv.y

lex.rules.c: rules.l
	flex rules.l

rules.tab.c: rules.y
	bison -d -Wcounterexamples rules.y


clean:
	rm -rf lex.* *.tab.* *.o