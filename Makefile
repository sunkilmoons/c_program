
program: main.o route-records.o
	gcc -Wall main.o route-records.o -o program

main.o: main.c route-records.h
	gcc -Wall -c main.c

route-records.o: route-records.c route-records.h
	gcc -Wall -c route-records.c

clean:
	rm *.o program