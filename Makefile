compile_and_run:
	g++ -o bin/8puzzle.o -I include/ src/*.cpp
	./bin/8puzzle.o
	
profiler: diagnostics strace

diagnostics: ./bin/8puzzle.o
	/usr/bin/time -v -p -o profile/system.log ./bin/8puzzle.o
	
strace: ./bin/8puzzle.o
	strace -o profile/strace.log ./bin/8puzzle.o
