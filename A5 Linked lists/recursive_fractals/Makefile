CC = g++ -std=c++11 -g
exe_file = run



all: $(exe_file)

$(exe_file): prog.cpp pattern.o
	$(CC) prog.cpp pattern.o -o $(exe_file)



pattern.o: pattern.cpp pattern.h
	$(CC) -c pattern.cpp

clean:
	rm -f *.o $(exe_file)