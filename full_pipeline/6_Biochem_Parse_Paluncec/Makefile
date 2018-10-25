CC = g++
DEBUG = #-g
PARALLEL = -std=c++11 -pthread
OPTIMIZE = -pipe -march=native -O2
LIB = -lpthread
CFLAGS = ${OPTIMIZE} ${PARALLEL} ${DEBUG} 
OBJS = Helberg_Functions.o BioChem.o BCPArrange.o Main.o

ProcessCodeBooks.exe: $(OBJS)
	$(CC) $(OBJS) -o ProcessCodeBooks.exe ${LIB}
	chmod 100 ProcessCodeBooks.exe

Helberg_Functions.o: Helberg_Functions.cpp Helberg_Functions.h
	 $(CC) ${CFLAGS} -c Helberg_Functions.cpp

BioChem.o: BioChem.cpp BioChem.h
	$(CC) ${CFLAGS} -c BioChem.cpp

BCPArrange.o: BCPArrange.cpp BCPArrange.h
	$(CC) ${CFLAGS} -c BCPArrange.cpp

Main.o: Main.cpp
	$(CC) ${CFLAGS} -c Main.cpp

.PHONY : clean
clean :
	-rm $(OBJS)
