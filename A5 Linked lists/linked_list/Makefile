CC = g++ -std=c++11
exe_file = run

all: $(exe_file)

$(exe_file): test_linked_list.o node.o linked_list.o
	$(CC) test_linked_list.o node.o linked_list.o -o $(exe_file)



node.o: node.cpp
	$(CC) -c node.cpp

linked_list.o: linked_list.cpp
	$(CC) -c linked_list.cpp

test_linked_list.o: test_linked_list.cpp
	$(CC) -c test_linked_list.cpp

clean:
	rm -f *.o $(exe_file)