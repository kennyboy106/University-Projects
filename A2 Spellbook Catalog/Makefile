CC = g++ -std=c++11
exe_file = run_wizard

all: $(exe_file)

clean:
	rm -f *.o $(exe_file)

catalog.o: catalog.cpp catalog.h
	$(CC) -c catalog.cpp

$(exe_file): catalog.o catalog.h run_wizard.cpp
	$(CC) catalog.o run_wizard.cpp -o $(exe_file)





