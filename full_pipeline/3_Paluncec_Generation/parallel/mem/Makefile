CC = g++
DEBUG = #-g
PARALLEL = -std=c++11 -pthread
OPTIMIZE = -O2 -pipe -march=native
LIB = -lpthread
CFLAGS = ${OPTIMIZE} ${PARALLEL} ${DEBUG} 
OBJS = Helberg_Functions.o Tenengolts.o Main.o

GenerateCodeBooks.exe: $(OBJS)
	$(CC) $(OBJS) -o GenerateCodeBooks.exe ${LIB}
	chmod 100 GenerateCodeBooks.exe

Helberg_Functions.o: Helberg_Functions.cpp Helberg_Functions.h
	 $(CC) ${CFLAGS} -c Helberg_Functions.cpp

Tenengolts.o: Tenengolts.cpp Tenengolts.h
	$(CC) ${CFLAGS} -c Tenengolts.cpp 

Main.o: Main.cpp 
	$(CC) ${CFLAGS} -c Main.cpp

.PHONY : clean
clean :
	-rm $(OBJS)
