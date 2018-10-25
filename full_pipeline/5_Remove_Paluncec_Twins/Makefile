CC = g++
DEBUG =# -g
PARALLEL = -std=c++11 #-pthread
OPTIMIZE = -O2 -pipe -march=native
LIB = #-lpthread
CFLAGS = ${OPTIMIZE} ${PARALLEL} ${DEBUG} 
OBJS = Check.o TwinToss.o

TossCodeBooks.exe: $(OBJS)
	$(CC) $(OBJS) -o TossCodeBooks.exe ${LIB}
	chmod 100 TossCodeBooks.exe

Check.o: Check.cpp Check.h
	 $(CC) ${CFLAGS} -c Check.cpp

TwinToss.o: TwinToss.cpp 
	$(CC) ${CFLAGS} -c TwinToss.cpp

.PHONY : clean
clean :
	-rm $(OBJS)
