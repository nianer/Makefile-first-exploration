objs = five.o six.o seven.o eight.o

main: one.o two.o three.o
	gcc -o main one.o two.o three.o

fourmain: four.o
	gcc -o fourmain four.o

fivemain: $(objs)
	gcc -o fivemain $(objs)

all: main fourmain fivemain

one.o: one.c first.h
	gcc -c one.c

two.o: two.c second.h
	gcc -c two.c

three.o: three.c third.h
	gcc -c three.c

four.o: four.c first.h second.h
	gcc -c four.c

five.o: five.c
	gcc -c five.c

six.o: six.c
	gcc -c six.c

seven.o: seven.c
	gcc -c seven.c

eight.o: eight.c
	gcc -c eight.c

clean:
	rm -f *main *.o