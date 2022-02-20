CPP=g++

objects=os2.o lru.o

SOURCE = os2.cpp lru.cpp

HEADER = os2.h lru.h

OUT = os2

FLAGS = -g -c 

all : $(objects)
	$(CPP) -g $(objects) -o $(OUT) 

os2.o : os2.cpp
	$(CPP) $(FLAGS) os2.cpp 

lru.o : lru.cpp
	$(CPP) $(FLAGS) lru.cpp 
	
clean:
	rm -f os2 $(objects)
