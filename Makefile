compile_and_run:
	g++ -o bin/EmergencyResponseSimulator.o -I include/ src/*.cpp
	./bin/EmergencyResponseSimulator.o
	
profiler: diagnostics strace

diagnostics: ./bin/EmergencyResponseSimulator.o
	/usr/bin/time -v -p -o profile/system.log ./bin/EmergencyResponseSimulator.o
	
strace: ./bin/EmergencyResponseSimulator.o
	strace -o profile/strace.log ./bin/EmergencyResponseSimulator.o
