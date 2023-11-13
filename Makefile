

pr: main.o set.o
	g++ main.o set.o -o pr

main.o: main.cpp set.h
	g++ -g -Wall -Wextra -Werror -pedantic -std=c++11 -c main.cpp

set.o: set.cpp set.h
	g++ -g -Wall -Wextra -Werror -pedantic -std=c++11 -c set.cpp

clean:
	rm -f *.o pr
