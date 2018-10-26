CC = g++
DEBUG = #-g
CFLAGS = -O2 -pipe -march=native ${DEBUG}
OBJS = Helberg_Functions.o BioChem.o BCPArrange.o

ProcessCodeBooks: $(OBJS)
	$(CC) $(OBJS) -o ProcessCodeBooks
	chmod 100 ProcessCodeBooks

Helberg_Functions.o: Helberg_Functions.cpp Helberg_Functions.h
	 $(CC) ${CFLAGS} -c Helberg_Functions.cpp

BioChem.o: BioChem.cpp BioChem.h
	$(CC) ${CFLAGS} -c BioChem.cpp

BCPArrange.o: BCPArrange.cpp BCPArrange.h
	$(CC) ${CFLAGS} -c BCPArrange.cpp

.PHONY : clean
clean :
	-rm $(OBJS)
