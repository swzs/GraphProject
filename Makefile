search-cli: main.o stats.o search.o
	cc -o search-cli main.o stats.o search.o

main.o: main.c stats.h search.h
	cc -c main.c search.c stats.c

stats.o: stats.c stats.h
        cc -c stats.c

search.o: search.c search.h stats.h
          cc -c search.c

clean:
        rm search-cli*.o


