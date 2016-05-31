CPPFLAGS=-std=c++11 -g

magic: hw02.o
	   g++ hw02.o -o magic

hw02.o: hw02.c hw02.h
		g++ $(CPPFLAGS) -c hw02.c

clean:
		rm *.o -f