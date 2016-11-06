CPPFLAGS = -Wall -O3 -std=c++11 -w -lm
PROGRAMS = main 

all: $(PROGRAMS)

main:main.cpp
	g++ -o main main.cpp $(CPPFLAGS)

clean:
	rm -f *.o $(PROGRAMS)
