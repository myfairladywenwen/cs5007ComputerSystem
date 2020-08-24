all: sort

sort: sort.h sort.c main.c
	gcc main.c sort.c -o sort -lm

run: sort
	./sort

clean: 
	rm sort *~
