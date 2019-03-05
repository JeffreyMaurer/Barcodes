CC = g++
DEBUG =# -g
PARALLEL = -std=c++11 -pthread
OPTIMIZE = -O2 -pipe -march=native
LIB = -lpthread
CFLAGS = ${OPTIMIZE} ${PARALLEL} ${DEBUG} 
OBJS = Check.o helper.o Tree.o main.o

Brute.exe: $(OBJS)
	$(CC) $(OBJS) -o Brute.exe ${LIB}
	chmod 100 Brute.exe

Check.o: Check.cpp Check.h
	$(CC) ${CFLAGS} -c Check.cpp

#node.o: node.h node.cpp
#	$(CC) ${CFLAGS} -c node.cpp

helper.o: helper.cpp helper.h
	$(CC) ${CFLAGS} -c helper.cpp

Tree.o: Tree.cpp Tree.h helper.h helper.cpp
	$(CC) ${CFLAGS} -c Tree.cpp 

main.o: main.cpp 
	$(CC) ${CFLAGS} -c main.cpp

.PHONY : clean
clean :
	-rm $(OBJS)
