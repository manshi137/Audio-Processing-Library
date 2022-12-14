all:
	g++ -c -Wall -Werror -fpic foo.cpp
	g++ -shared -o libaudio.so foo.o -I /usr/local/Cellar/openblas/0.3.19/include -L /usr/local/Cellar/openblas/0.3.19/lib -lopenblas -lm -ldl
	g++ -L /Users/manshisagar/Desktop/cop290/subtask3 -Wall -o yourcode.out main.cpp -laudio -I /usr/local/Cellar/openblas/0.3.19/include -L /usr/local/Cellar/openblas/0.3.19/lib -lopenblas -lm -ldl
	LD_LIBRARY_PATH=/Users/manshisagar/Desktop/cop290/subtask3:$LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=/Users/manshisagar/Desktop/cop290/subtask3:$LD_LIBRARY_PATH
	
		

clean:
	rm -f yourcode.out