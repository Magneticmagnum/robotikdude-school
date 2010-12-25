CPP = g++
#CFLAGS = -c -g

all: executable

.SUFFIXES : .o .cpp
%.o : %.cpp
	$(CPP) -c -g $< -o $@

OBJS = KeyValueComparator.o

KeyValueComparator.o: KeyValueComparator.h KeyValueComparator.cpp

executable: $(OBJS) Main.cpp
	$(CPP) -o main $(OBJS) Main.cpp

clean:
	rm -f *.o main